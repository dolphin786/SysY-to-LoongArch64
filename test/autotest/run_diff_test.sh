#!/bin/bash
# set -euo pipefail  # 严格模式：暂时不启用，以便在差分测试中继续执行

# 配置路径
DIFF_TEST_DIR="diff_test_cases"
TEMP_DIR="build/diff_tests"
RESULTS_DIR="$TEMP_DIR/results"
mkdir -p "$DIFF_TEST_DIR" "$TEMP_DIR" "$RESULTS_DIR"

# 调整系统栈限制
original_soft=$(ulimit -Ss)

# 定义恢复函数
restore_stack_limit() {
  echo "恢复原始栈限制..."
  ulimit -Ss "$original_soft" 2>/dev/null || echo "恢复软限制失败（需要权限或超出硬限制）"
}

# 注册退出时的恢复操作
trap restore_stack_limit EXIT

# 设置临时栈限制为新值（1GB）
new_limit=1048576  # 1024 * 1024 KB = 1GB
echo "当前系统栈限制（ulimit -s）：$(ulimit -s) KB"
echo "尝试设置临时栈限制为 $((new_limit / 1024)) MB..."
if ! ulimit -Ss "$new_limit"; then
  echo "错误：无法设置栈限制到 $new_limit KB"
  exit 1
fi

# 结果统计
declare -i PASS=0 FAIL=0 TOTAL=0

echo "===== 开始差分测试 ====="

# 步骤1: 使用generate_sysy_test.py生成测试样例
echo "生成测试样例..."


# 生成几个随机测试样例
for i in {1..256}; do
    echo "生成随机测试样例 $i..."
    python3 -c "
import sys
sys.path.append('.')
from generate_sysy_test import *
program = generate_sysy_program()
program = verify_no_increment_decrement(program)
program = check_and_fix_assignments(program)
program = ensure_returns_have_values(program)
with open('$DIFF_TEST_DIR/random_test_$i.sy', 'w') as f:
    f.write(program)
"
done

# 定义关键路径
SYSROOT="/opt/cross-tools/target"
GCC_LIB_PATH="/opt/cross-tools/lib/gcc/loongarch64-unknown-linux-gnu/13.0.0"

# 遍历所有生成的.sy测试样例
for sy_file in "$DIFF_TEST_DIR"/*.sy; do
    # 生成基础名称
    base_name=$(basename "$sy_file" .sy)
    echo "-----------------------------------------"
    echo "差分测试 $base_name:"
    ((TOTAL++))

    # 文件路径
    your_ll_file="$TEMP_DIR/${base_name}_your.ll"
    your_asm_file="$TEMP_DIR/${base_name}_your.s"
    clang_ll_file="$TEMP_DIR/${base_name}_clang.ll"
    your_exe_file="$TEMP_DIR/${base_name}_your.exe"
    clang_exe_file="$TEMP_DIR/${base_name}_clang.exe"
    your_out_file="$RESULTS_DIR/${base_name}_your.out"
    clang_out_file="$RESULTS_DIR/${base_name}_clang.out"
    diff_result="$RESULTS_DIR/${base_name}_diff.txt"

    # 步骤1: 使用您的编译器生成ASM
    echo "  使用您的编译器生成ASM... "
    if ./build/SysYAsmAutoTester "$sy_file" "$your_asm_file" &>/dev/null; then
        echo "  ✓ 成功"
    else
        echo "  ✗ 失败 - 您的编译器无法生成ASM"
        echo "    跳过此测试案例并继续下一个"
        ((FAIL++))
        continue
    fi

    # 步骤2: 使用clang生成LLVM IR
    echo "  使用clang生成IR... "
    if clang-16 -x c -std=c11 -target loongarch64-unknown-linux-gnu -mabi=lp64d -S -emit-llvm -O0 -nostdinc -o "$clang_ll_file" "$sy_file" &>/dev/null; then
        echo "  ✓ 成功"
    else
        echo "  ✗ 失败 - clang无法编译此测试案例"
        echo "    这可能表明测试案例有语法错误，跳过"
        # ((FAIL++))
        continue
    fi

    # 步骤3: 编译和链接您的ASM
    echo "  编译链接您的ASM... "
    if clang-16 -g -target loongarch64-unknown-linux-gnu -mabi=lp64d --sysroot="$SYSROOT" -c sylib.c -o sylib.o \
        && clang-16 -g -target loongarch64-unknown-linux-gnu -mabi=lp64d --sysroot="$SYSROOT" -Wno-override-module -c "$your_asm_file" -o "${your_asm_file%.*}.o" \
        && clang-16 -g -target loongarch64-unknown-linux-gnu -mabi=lp64d -fuse-ld=bfd -static \
        --sysroot="$SYSROOT" \
        -L "$SYSROOT/usr/lib64" \
        -L "$GCC_LIB_PATH" \
        -Wl,-z,stack-size=104857600 \
        "${your_asm_file%.*}.o" sylib.o \
        -lgcc \
        -lc \
        "$SYSROOT/usr/lib64/crtn.o" \
        -o "$your_exe_file"; then
        echo "  ✓ 成功"
    else
        echo "  ✗ 失败 - 您的IR编译/链接错误"
        ((FAIL++))
        continue
    fi

    # 步骤4: 编译和链接clang的IR
    echo "  编译链接clang的IR... "
    if clang-16 -g -target loongarch64-unknown-linux-gnu -mabi=lp64d --sysroot="$SYSROOT" -Wno-override-module -c "$clang_ll_file" -S -o "${clang_ll_file%.*}.s" \
        && clang-16 -g -target loongarch64-unknown-linux-gnu -mabi=lp64d --sysroot="$SYSROOT" -Wno-override-module -c "$clang_ll_file" -o "${clang_ll_file%.*}.o" \
        && clang-16 -g -target loongarch64-unknown-linux-gnu -mabi=lp64d -fuse-ld=bfd -static \
        --sysroot="$SYSROOT" \
        -L "$SYSROOT/usr/lib64" \
        -L "$GCC_LIB_PATH" \
        -Wl,-z,stack-size=104857600 \
        "${clang_ll_file%.*}.o" sylib.o \
        -lgcc \
        -lc \
        "$SYSROOT/usr/lib64/crtn.o" \
        -o "$clang_exe_file"; then
        echo "  ✓ 成功"
    else
        echo "  ✗ 失败 - clang的IR编译/链接错误"
        ((FAIL++))
        continue
    fi

    # 步骤5: 运行两个可执行文件
    echo "  执行您的编译结果... "
    qemu-loongarch64 "$your_exe_file" > "$your_out_file" 2>&1
    your_exit_code=$?
    echo "" >> "$your_out_file"
    echo "$your_exit_code" >> "$your_out_file"
    
    # 删除输出的第一行（计时信息）
    sed -i '1d' "$your_out_file"
    
    echo "  执行clang的编译结果... "
    qemu-loongarch64 "$clang_exe_file" > "$clang_out_file" 2>&1
    clang_exit_code=$?
    echo "" >> "$clang_out_file"
    echo "$clang_exit_code" >> "$clang_out_file"

    # 删除输出的第一行（计时信息）
    sed -i '1d' "$clang_out_file"

    # 步骤6: 比较输出
    echo "  比较结果... "
    if diff -bB -q "$your_out_file" "$clang_out_file" &>/dev/null; then
        echo "  ✓ 输出结果一致"
        ((PASS++))
    else
        echo "  ✗ 输出结果不一致"
        echo "  比较差异:"
        diff -bB "$your_out_file" "$clang_out_file" > "$diff_result"
        cat "$diff_result"
        ((FAIL++))
    fi
done

# 汇总结果
echo "===== 差分测试完成 ====="
echo "总计测试: $TOTAL"
echo "通过: $PASS  失败: $FAIL"

# 计算通过率
if [ $TOTAL -gt 0 ]; then
    pass_rate=$(echo "scale=2; $PASS * 100 / $TOTAL" | bc)
    echo "通过率: ${pass_rate}%"
fi

exit $((FAIL > 0 ? 1 : 0))  # 返回非0状态码如果有失败
