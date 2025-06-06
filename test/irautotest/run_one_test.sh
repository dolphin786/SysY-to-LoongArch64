#!/bin/bash
#set -euo pipefail  # 严格模式：错误自动退出、未定义变量报错

# 配置路径
# TEST_CASES_DIR="functional_cases"
TEST_CASES_DIR="critical_cases"
TEMP_DIR="build/tests"
mkdir -p "$TEMP_DIR"
LIB_PATH="libsysy.a"          # libsysy.a 位于当前目录 (./test/autotest/)


# 指定测试的样例
TEST_CASE="95_float"

# 结果统计
declare -i PASS=0 FAIL=0


# 步骤 1: 保存原始的栈软限制和硬限制
original_soft=$(ulimit -Ss)
# original_hard=$(ulimit -Hs)

# 步骤 2: 定义恢复函数
restore_stack_limit() {
  echo "恢复原始栈限制..."
  ulimit -Ss "$original_soft" 2>/dev/null || echo "恢复软限制失败（需要权限或超出硬限制）"
}

# 步骤 3: 注册退出时的恢复操作（捕获所有退出信号）
trap restore_stack_limit EXIT

# 步骤 4: 设置临时栈限制为新值（例如 1GB）
new_limit=1048576  # 1024 * 1024 KB = 1GB
echo "当前系统栈限制（ulimit -s）：$(ulimit -s) KB"
echo "尝试设置临时栈限制为 $((new_limit / 1024)) MB..."
if ! ulimit -Ss "$new_limit"; then
  echo "错误：无法设置栈限制到 $new_limit KB"
  exit 1
fi


echo "===== 开始自动化测试 ====="

# 遍历所有 .sy 测试样例
for sy_file in "$TEST_CASES_DIR"/*.sy; do
    # 生成基础名称 (e.g., 00_main)
    base_name=$(basename "$sy_file" .sy)
    if [ "$base_name" != "$TEST_CASE" ]; then continue; fi
    
    # if [ "$base_name" != "00_main" ]; then continue; fi
    # if [ "$base_name" != "21_if_test2" ]; then continue; fi
    echo "测试 $base_name:"

    # 提取相关文件路径
    in_file="$TEST_CASES_DIR/$base_name.in"
    out_file="$TEST_CASES_DIR/$base_name.out"
    ll_file="$TEMP_DIR/$base_name.ll"
    exe_file="$TEMP_DIR/$base_name.exe"
    actual_out="$TEMP_DIR/$base_name.actual"

    # 步骤 1: 生成LLVM IR
    echo -n "  生成IR... "
    if ./build/SysYIRGeneratorAutoTester "$sy_file" "$ll_file" ; then
        echo "成功"
    else
        echo "失败"
        echo "  ⚠️ IR生成异常"
        ((FAIL++))
        continue
    fi

    # # 步骤 2: 编译IR并链接库
    # echo -n "  编译链接... "
    # if clang -Wno-override-module "$ll_file" "$LIB_PATH" -o "$exe_file" ; then
    #     echo "成功"
    # else
    #     echo "失败"
    #     echo "  ⚠️ 编译/链接错误"
    #     ((FAIL++))
    #     continue
    # fi

    echo -n "  编译链接... "
    # 编译sylib.c、LLVM IR，并链接，加了-g选项用于包含调试符号
    if clang -g -c sylib.c -o sylib.o \
        && clang -g -Wno-override-module -c "$ll_file" -o "${ll_file%.*}.o" \
        && clang -g -Wl,-z,stack-size=104857600 "${ll_file%.*}.o" sylib.o -o "$exe_file"; then
        echo "成功"
    else
        echo "失败"
        echo "  ⚠️ 编译/链接错误"
        ((FAIL++))
        continue
    fi

    # 步骤 3: 运行可执行文件 
    echo -n "  执行测试... "
    if [ -f "$in_file" ]; then
        "$exe_file" <"$in_file" >"$actual_out" 2>&1
        exit_code=$?      # 保存退出码
        echo "" >> "$actual_out"
        echo "$exit_code" >> "$actual_out" # 将退出码追加到文件末尾（保留原有内容）
    else
        "$exe_file" >"$actual_out" 2>&1
        # "$exe_file"
        exit_code=$?      # 保存退出码
        echo "" >> "$actual_out"
        echo "$exit_code" >> "$actual_out" # 将退出码追加到文件末尾（保留原有内容）
    fi
    echo "完成"

    #删除输出的第一行，即计时
    sed -i '1d' "$actual_out"
    
    # 步骤 4: 比较输出
    echo -n "  验证结果... "
    if [ ! -f "$out_file" ]; then
        echo "⚠️ 缺少预期输出文件"
        ((FAIL++))
        continue
    fi

    # 使用diff忽略行末空格差异 (-b) 和空行差异 (-B)
    if diff -bB -q "$actual_out" "$out_file" &>/dev/null; then
        echo "一致"
        ((PASS++))
    else
        echo "不一致"
        echo "预期输出:"
        cat "$out_file"
        echo "实际输出:"
        cat "$actual_out"
        ((FAIL++))
    fi
done

# 汇总结果
echo "===== 测试完成 ====="
echo "通过: $PASS  失败: $FAIL"
exit $((FAIL > 0 ? 1 : 0))  # 返回非0状态码如果有失败