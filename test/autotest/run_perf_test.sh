#!/bin/bash
# 性能测试脚本：比较您的SysY编译器与GCC的运行性能

# 设置严格错误处理
set -uo pipefail

# 配置路径
PERF_TEST_DIR="${PERF_TEST_DIR:-perf_test_cases}"
TEMP_DIR="build/perf_tests"
RESULTS_DIR="$TEMP_DIR/results"
REPORT_FILE="performance_report.txt"
TEMP_TEST_DIR="$TEMP_DIR/gen_tests"  # 存放生成的测试样例的临时目录
SYSROOT="/opt/cross-tools/target"
GCC_LIB_PATH="/opt/cross-tools/lib/gcc/loongarch64-unknown-linux-gnu/13.0.0"

# 命令行参数处理
GENERATE_FLOAT_TESTS=false
GENERATE_INT_TESTS=false
VERIFY_RESULTS=true
TEST_COUNT=10
GCC_OPT_LEVEL=1
RUN_COUNT=3  # 每个样例运行的次数

function show_usage {
    echo "用法: $0 [选项]"
    echo "选项:"
    echo "  -f, --float       使用generate_perf_test.py生成浮点性能测试案例"
    echo "  -i, --int         使用generate_sysy_test.py生成整数测试案例"
    echo "  -n, --no-verify   不验证结果正确性"
    echo "  -c, --count N     生成N个测试案例 (默认: 10)"
    echo "  -r, --run-count N 每个测试案例运行N次 (默认: 3)"
    echo "  -o, --opt-level N 设置GCC优化级别 (默认: 1)"
    echo "  -d, --directory DIR 设置测试目录 (默认: $PERF_TEST_DIR)"
    echo "  -h, --help        显示此帮助信息"
}

# 处理命令行参数
while [[ $# -gt 0 ]]; do
    case $1 in
        -f|--float)
            GENERATE_FLOAT_TESTS=true
            shift
            ;;
        -i|--int)
            GENERATE_INT_TESTS=true
            shift
            ;;
        -n|--no-verify)
            VERIFY_RESULTS=false
            shift
            ;;
        -c|--count)
            TEST_COUNT="$2"
            shift 2
            ;;
        -r|--run-count)
            RUN_COUNT="$2"
            shift 2
            ;;
        -o|--opt-level)
            GCC_OPT_LEVEL="$2"
            shift 2
            ;;
        -d|--directory)
            PERF_TEST_DIR="$2"
            shift 2
            ;;
        -h|--help)
            show_usage
            exit 0
            ;;
        *)
            echo "未知选项: $1"
            show_usage
            exit 1
            ;;
    esac
done

# 创建必要的目录
mkdir -p "$TEMP_DIR" "$RESULTS_DIR"

# 如果要生成测试案例，创建并清空临时测试目录
if $GENERATE_FLOAT_TESTS || $GENERATE_INT_TESTS; then
    echo "清空临时测试目录 $TEMP_TEST_DIR..."
    rm -rf "$TEMP_TEST_DIR"
    mkdir -p "$TEMP_TEST_DIR"
    PERF_TEST_DIR="$TEMP_TEST_DIR"  # 使用临时目录作为测试目录
else
    mkdir -p "$PERF_TEST_DIR"  # 确保测试目录存在
fi

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

# 解析时间字符串为微秒
parse_time() {
    local time_str="$1"
    local hours=0
    local minutes=0
    local seconds=0
    local microseconds=0
    
    if [[ $time_str =~ ([0-9]+)H-([0-9]+)M-([0-9]+)S-([0-9]+)us ]]; then
        hours="${BASH_REMATCH[1]}"
        minutes="${BASH_REMATCH[2]}"
        seconds="${BASH_REMATCH[3]}"
        microseconds="${BASH_REMATCH[4]}"
        
        # 将所有单位转换为微秒
        echo $(( 
            hours * 3600 * 1000000 + 
            minutes * 60 * 1000000 + 
            seconds * 1000000 + 
            microseconds 
        ))
    else
        echo "0" # 解析失败返回0
    fi
}

# 格式化微秒为可读时间
format_time() {
    local microseconds="$1"
    local total_seconds=$(( microseconds / 1000000 ))
    local hours=$(( total_seconds / 3600 ))
    local minutes=$(( (total_seconds % 3600) / 60 ))
    local seconds=$(( total_seconds % 60 ))
    local ms=$(( (microseconds % 1000000) / 1000 ))
    
    echo "${hours}h ${minutes}m ${seconds}.${ms}s"
}

# 生成测试案例函数 - 整数测试
generate_int_test_cases() {
    echo "===== 生成整数测试案例 ====="
    
    # 检查生成脚本是否存在
    if [[ ! -f "generate_sysy_test.py" ]]; then
        echo "错误: generate_sysy_test.py 不存在!"
        exit 1
    fi
    
    # 生成标准SysY测试案例
    for i in $(seq 1 $TEST_COUNT); do
        echo "生成随机SysY整数测试案例 $i..."
        python3 -c "
import sys
sys.path.append('.')
from generate_sysy_test import *
program = generate_sysy_program(num_funcs=8, include_globals=True)
program = verify_no_increment_decrement(program)
program = check_and_fix_assignments(program)
program = ensure_returns_have_values(program)
with open('$TEMP_TEST_DIR/int_test_$i.sy', 'w') as f:
    f.write(program)
"
    done
    
    echo "整数测试案例生成完成。"
}

# 生成测试案例函数 - 浮点测试
generate_float_test_cases() {
    echo "===== 生成浮点性能测试案例 ====="
    
    # 检查生成脚本是否存在
    if [[ ! -f "generate_perf_test.py" ]]; then
        echo "错误: generate_perf_test.py 不存在!"
        exit 1
    fi
    
    echo "生成专门的浮点性能测试案例..."
    python3 generate_perf_test.py
    
    # 移动生成的文件到临时测试目录
    if [[ -f "sysy_float_perf_test.c" ]]; then
        mv sysy_float_perf_test.c "$TEMP_TEST_DIR/sysy_float_perf_test.sy"
        echo "生成的测试: sysy_float_perf_test.sy"
    fi
    if [[ -f "matrix_multiplication_test.c" ]]; then
        mv matrix_multiplication_test.c "$TEMP_TEST_DIR/matrix_multiplication_test.sy"
        echo "生成的测试: matrix_multiplication_test.sy"
    fi
    if [[ -f "iterative_computation_test.c" ]]; then
        mv iterative_computation_test.c "$TEMP_TEST_DIR/iterative_computation_test.sy"
        echo "生成的测试: iterative_computation_test.sy"
    fi
    
    # 如果生成的测试案例不够，额外生成一些浮点测试
    current_count=$(ls -1 "$TEMP_TEST_DIR"/*.sy 2>/dev/null | wc -l)
    
    if [ "$current_count" -lt "$TEST_COUNT" ]; then
        additional_needed=$((TEST_COUNT - current_count))
        echo "生成额外 $additional_needed 个浮点测试案例..."
        
        for i in $(seq 1 $additional_needed); do
            echo "生成随机SysY浮点测试案例 $i..."
            python3 -c "
import sys
sys.path.append('.')
from generate_sysy_test import *
program = generate_sysy_program(with_float=True, loops_depth=3, max_stmts=20)
program = verify_no_increment_decrement(program)
program = check_and_fix_assignments(program)
program = ensure_returns_have_values(program)
with open('$TEMP_TEST_DIR/float_test_$i.sy', 'w') as f:
    f.write(program)
"
        done
    fi
    
    echo "浮点性能测试案例生成完成。"
}

# 如果需要，生成测试案例
if $GENERATE_INT_TESTS; then
    generate_int_test_cases
fi

if $GENERATE_FLOAT_TESTS; then
    generate_float_test_cases
fi

echo "===== 开始性能测试 ====="

# 初始化报告文件
echo "SysY编译器性能测试报告" > "$REPORT_FILE"
echo "======================" >> "$REPORT_FILE"
echo "测试日期: $(date)" >> "$REPORT_FILE"
echo "GCC优化级别: -O$GCC_OPT_LEVEL" >> "$REPORT_FILE"
echo "验证结果: $(if $VERIFY_RESULTS; then echo "是"; else echo "否"; fi)" >> "$REPORT_FILE"
echo "每个测试运行次数: $RUN_COUNT" >> "$REPORT_FILE"
echo >> "$REPORT_FILE"
echo "测试结果" >> "$REPORT_FILE"
echo "--------" >> "$REPORT_FILE"
printf "%-30s %-15s %-15s %-15s %-10s %-15s\n" "测试案例" "SysY编译器(秒)" "GCC(秒)" "比率(SysY/GCC)" "验证结果" "编译状态" >> "$REPORT_FILE"
echo "-------------------------------------------------------------------------------------" >> "$REPORT_FILE"

# 结果统计
declare -i TOTAL_TESTS=0 SUCCESSFUL_TESTS=0 VERIFICATION_PASSED=0
declare -i COMPILATION_ERRORS=0
TOTAL_SYSY_TIME=0
TOTAL_GCC_TIME=0

# 遍历所有.sy测试案例
for sy_file in "$PERF_TEST_DIR"/*.sy; do
    # 检查文件是否存在
    if [ ! -f "$sy_file" ]; then
        echo "没有找到测试文件。请先生成测试案例（使用-f或-i选项）或检查测试目录。"
        exit 1
    fi
    
    # 生成基础名称
    base_name=$(basename "$sy_file" .sy)
    echo "-----------------------------------------"
    echo "性能测试 $base_name:"
    ((TOTAL_TESTS++))

    # 文件路径
    your_ll_file="$TEMP_DIR/${base_name}_sysy.ll"
    your_asm_file="$TEMP_DIR/${base_name}_sysy.s"
    your_exe_file="$TEMP_DIR/${base_name}_sysy.exe"
    gcc_exe_file="$TEMP_DIR/${base_name}_gcc.exe"
    your_out_file="$RESULTS_DIR/${base_name}_sysy.out"
    gcc_out_file="$RESULTS_DIR/${base_name}_gcc.out"
    
    compilation_status="成功"
    verification_status="N/A"
    
    # 步骤1: 使用您的编译器生成LLVM IR
    echo "  使用您的SysY编译器生成IR... "
    if ./build/SysYAsmAutoTester "$sy_file" "$your_asm_file" &>/dev/null; then
        echo "  ✓ 成功"
    else
        echo "  ✗ 失败 - 您的编译器无法生成IR"
        compilation_status="SysY编译失败"
        ((COMPILATION_ERRORS++))
        printf "%-30s %-15s %-15s %-15s %-10s %-15s\n" "$base_name" "N/A" "N/A" "N/A" "N/A" "$compilation_status" >> "$REPORT_FILE"
        continue
    fi

    # 步骤2: 编译和链接您的IR
    echo "  编译链接您的IR... "
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
        -lm \
        "$SYSROOT/usr/lib64/crtn.o" \
        -o "$your_exe_file"; then
        echo "  ✓ 成功"
    else
        echo "  ✗ 失败 - 您的IR编译/链接错误"
        compilation_status="链接失败"
        ((COMPILATION_ERRORS++))
        printf "%-30s %-15s %-15s %-15s %-10s %-15s\n" "$base_name" "N/A" "N/A" "N/A" "N/A" "$compilation_status" >> "$REPORT_FILE"
        continue
    fi

    # 步骤3: 使用GCC编译
    echo "  使用GCC编译... "
    if loongarch64-unknown-linux-gnu-gcc -x c -O"$GCC_OPT_LEVEL" -static "$sy_file" sylib.c -include sylib.h -o "$gcc_exe_file" -lm -fcommon; then
        echo "  ✓ 成功"
    else
        echo "  ✗ 失败 - GCC编译错误"
        compilation_status="GCC编译失败"
        ((COMPILATION_ERRORS++))
        printf "%-30s %-15s %-15s %-15s %-10s %-15s\n" "$base_name" "N/A" "N/A" "N/A" "N/A" "$compilation_status" >> "$REPORT_FILE"
        continue
    fi

    # # 步骤4: 运行两个可执行文件并测量性能
    # ((SUCCESSFUL_TESTS++))
    
    # # 进行验证（如果需要）
    # if $VERIFY_RESULTS; then
    #     echo "  验证结果一致性... "
    #     qemu-loongarch64 "$your_exe_file" > "$your_out_file" 2>/dev/null
    #     your_exit_code=$?
    #     echo "" >> "$your_out_file"
    #     echo "$your_exit_code" >> "$your_out_file"
        
    #     qemu-loongarch64 "$gcc_exe_file" > "$gcc_out_file" 2>/dev/null
    #     gcc_exit_code=$?
    #     echo "" >> "$gcc_out_file"
    #     echo "$gcc_exit_code" >> "$gcc_out_file"
        
    #     if diff -bB -q "$your_out_file" "$gcc_out_file" &>/dev/null; then
    #         echo "  ✓ 输出结果一致"
    #         verification_status="通过"
    #         ((VERIFICATION_PASSED++))
    #     else
    #         echo "  ✗ 输出结果不一致"
    #         echo "  请注意: 由于结果不一致，性能比较可能不准确"
    #         verification_status="失败"
    #         # 如果验证失败，可以选择跳过性能测试
    #         printf "%-30s %-15s %-15s %-15s %-10s %-15s\n" \
    #             "$base_name" \
    #             "N/A" \
    #             "N/A" \
    #             "N/A" \
    #             "$verification_status" \
    #             "$compilation_status" >> "$REPORT_FILE"
    #         continue
    #     fi
    # else
    #     verification_status="跳过"
    # fi
    
    # # 性能测试 - 多次运行取平均
    # echo "  执行性能测试 ($RUN_COUNT 次)..."
    
    # your_total_time_us=0
    # gcc_total_time_us=0
    
    # for run in $(seq 1 $RUN_COUNT); do
    #     echo "    运行 $run/$RUN_COUNT:"
        
    #     # 运行您的编译结果
    #     echo "      您的SysY编译器... "
    #     your_err_file="$RESULTS_DIR/${base_name}_sysy_run${run}.err"
    #     qemu-loongarch64 "$your_exe_file" >/dev/null 2>"$your_err_file"
        
    #     # 检查stderr中的时间信息
    #     your_time_str=$(grep -oE "TOTAL: [0-9]+H-[0-9]+M-[0-9]+S-[0-9]+us" "$your_err_file" | awk '{print $2}')
    #     if [ -z "$your_time_str" ]; then
    #         your_time_str="0H-0M-0S-0us"  # 默认值
    #     fi
    #     your_time_us=$(parse_time "$your_time_str")
    #     your_total_time_us=$((your_total_time_us + your_time_us))
    #     your_time_readable=$(format_time "$your_time_us")
    #     echo "      时间: $your_time_readable"
        
    #     # 运行GCC的编译结果
    #     echo "      GCC... "
    #     gcc_err_file="$RESULTS_DIR/${base_name}_gcc_run${run}.err"
    #     qemu-loongarch64 "$gcc_exe_file" >/dev/null 2>"$gcc_err_file"
        
    #     # 检查stderr中的时间信息
    #     gcc_time_str=$(grep -oE "TOTAL: [0-9]+H-[0-9]+M-[0-9]+S-[0-9]+us" "$gcc_err_file" | awk '{print $2}')
    #     if [ -z "$gcc_time_str" ]; then
    #         gcc_time_str="0H-0M-0S-0us"  # 默认值
    #     fi
    #     gcc_time_us=$(parse_time "$gcc_time_str")
    #     gcc_total_time_us=$((gcc_total_time_us + gcc_time_us))
    #     gcc_time_readable=$(format_time "$gcc_time_us")
    #     echo "      时间: $gcc_time_readable"
    # done




    # 步骤4: 运行两个可执行文件并测量性能
    ((SUCCESSFUL_TESTS++))

    # 检查是否存在对应的.in文件
    base_file_path="${PERF_TEST_DIR}/${base_name}"
    input_file="${base_file_path}.in"
    has_input=false
    if [ -f "$input_file" ]; then
        has_input=true
        echo "  检测到输入文件: $(basename "$input_file")"
    fi

    # 进行验证（如果需要）
    if $VERIFY_RESULTS; then
        echo "  验证结果一致性... "

        # 准备参考输出
        reference_output="${base_file_path}.out"
        reference_out_exists=false
        if [ -f "$reference_output" ]; then
            reference_out_exists=true
            echo "  检测到参考输出文件: $(basename "$reference_output")"
        fi

        # 运行您的编译结果进行验证
        your_out_file="$RESULTS_DIR/${base_name}_sysy.out"
        if $has_input; then
            # 有输入文件时
            qemu-loongarch64 "$your_exe_file" < "$input_file" > "$your_out_file" 2>/dev/null
        else
            # 无输入文件时
            qemu-loongarch64 "$your_exe_file" > "$your_out_file" 2>/dev/null
        fi
        your_exit_code=$?
        echo "" >> "$your_out_file"
        echo "$your_exit_code" >> "$your_out_file"
        
        # 运行GCC的编译结果进行验证
        gcc_out_file="$RESULTS_DIR/${base_name}_gcc.out"
        if $has_input; then
            # 有输入文件时
            qemu-loongarch64 "$gcc_exe_file" < "$input_file" > "$gcc_out_file" 2>/dev/null
        else
            # 无输入文件时
            qemu-loongarch64 "$gcc_exe_file" > "$gcc_out_file" 2>/dev/null
        fi
        gcc_exit_code=$?
        echo "" >> "$gcc_out_file"
        echo "$gcc_exit_code" >> "$gcc_out_file"
        
        # 验证输出
        verification_passed=false
        
        # 首先检查您的编译器输出与GCC输出是否一致
        if diff -bB -q "$your_out_file" "$gcc_out_file" &>/dev/null; then
            verification_passed=true
        fi
        
        # 如果存在参考输出文件，还需要与参考输出比较
        if $reference_out_exists; then
            if ! diff -bB -q "$your_out_file" "$reference_output" &>/dev/null; then
                verification_passed=false
                echo "  ✗ 与参考输出不一致"
            fi
        fi
        
        if $verification_passed; then
            echo "  ✓ 输出结果一致"
            verification_status="通过"
            ((VERIFICATION_PASSED++))
        else
            echo "  ✗ 输出结果不一致"
            echo "  请注意: 由于结果不一致，性能比较可能不准确"
            verification_status="失败"
            # 如果验证失败，可以选择跳过性能测试
            printf "%-30s %-15s %-15s %-15s %-10s %-15s\n" \
                "$base_name" \
                "N/A" \
                "N/A" \
                "N/A" \
                "$verification_status" \
                "$compilation_status" >> "$REPORT_FILE"
            continue
        fi
    else
        verification_status="跳过"
    fi

    # 性能测试 - 多次运行取平均
    echo "  执行性能测试 ($RUN_COUNT 次)..."

    your_total_time_us=0
    gcc_total_time_us=0

    for run in $(seq 1 $RUN_COUNT); do
        echo "    运行 $run/$RUN_COUNT:"
        
        # 运行您的编译结果
        echo "      您的SysY编译器... "
        your_err_file="$RESULTS_DIR/${base_name}_sysy_run${run}.err"
        if $has_input; then
            # 有输入文件时
            qemu-loongarch64 "$your_exe_file" < "$input_file" >/dev/null 2>"$your_err_file"
        else
            # 无输入文件时
            qemu-loongarch64 "$your_exe_file" >/dev/null 2>"$your_err_file"
        fi
        
        # 检查stderr中的时间信息
        your_time_str=$(grep -oE "TOTAL: [0-9]+H-[0-9]+M-[0-9]+S-[0-9]+us" "$your_err_file" | awk '{print $2}')
        if [ -z "$your_time_str" ]; then
            your_time_str="0H-0M-0S-0us"  # 默认值
        fi
        your_time_us=$(parse_time "$your_time_str")
        your_total_time_us=$((your_total_time_us + your_time_us))
        your_time_readable=$(format_time "$your_time_us")
        echo "      时间: $your_time_readable"
        
        # 运行GCC的编译结果
        echo "      GCC... "
        gcc_err_file="$RESULTS_DIR/${base_name}_gcc_run${run}.err"
        if $has_input; then
            # 有输入文件时
            qemu-loongarch64 "$gcc_exe_file" < "$input_file" >/dev/null 2>"$gcc_err_file"
        else
            # 无输入文件时
            qemu-loongarch64 "$gcc_exe_file" >/dev/null 2>"$gcc_err_file"
        fi
        
        # 检查stderr中的时间信息
        gcc_time_str=$(grep -oE "TOTAL: [0-9]+H-[0-9]+M-[0-9]+S-[0-9]+us" "$gcc_err_file" | awk '{print $2}')
        if [ -z "$gcc_time_str" ]; then
            gcc_time_str="0H-0M-0S-0us"  # 默认值
        fi
        gcc_time_us=$(parse_time "$gcc_time_str")
        gcc_total_time_us=$((gcc_total_time_us + gcc_time_us))
        gcc_time_readable=$(format_time "$gcc_time_us")
        echo "      时间: $gcc_time_readable"
    done

    

    
    # 计算平均时间
    your_avg_time_us=$((your_total_time_us / RUN_COUNT))
    gcc_avg_time_us=$((gcc_total_time_us / RUN_COUNT))
    
    your_avg_readable=$(format_time $your_avg_time_us)
    gcc_avg_readable=$(format_time $gcc_avg_time_us)
    
    # 更新总时间
    TOTAL_SYSY_TIME=$((TOTAL_SYSY_TIME + your_avg_time_us))
    TOTAL_GCC_TIME=$((TOTAL_GCC_TIME + gcc_avg_time_us))
    
    # 计算性能比率
    if [ "$gcc_avg_time_us" -eq 0 ]; then
        ratio="无效"
    else
        ratio=$(echo "scale=3; $your_avg_time_us / $gcc_avg_time_us" | bc)
    fi
    
    # 步骤6: 显示性能结果
    echo "  性能结果 (平均 $RUN_COUNT 次):"
    echo "    您的SysY编译器: $your_avg_readable"
    echo "    GCC: $gcc_avg_readable"
    echo "    比率(SysY/GCC): $ratio"
    
    # 添加到报告
    printf "%-30s %-15s %-15s %-15s %-10s %-15s\n" \
        "$base_name" \
        "$your_avg_readable" \
        "$gcc_avg_readable" \
        "$ratio" \
        "$verification_status" \
        "$compilation_status" >> "$REPORT_FILE"
done

# 计算总体性能比率
if [ "$TOTAL_GCC_TIME" -eq 0 ]; then
    total_ratio="无法计算"
else
    total_ratio=$(echo "scale=3; $TOTAL_SYSY_TIME / $TOTAL_GCC_TIME" | bc)
fi

# 添加汇总信息到报告
echo >> "$REPORT_FILE"
echo "性能测试汇总" >> "$REPORT_FILE"
echo "------------" >> "$REPORT_FILE"
echo "测试总数: $TOTAL_TESTS" >> "$REPORT_FILE"
echo "编译成功: $SUCCESSFUL_TESTS" >> "$REPORT_FILE"
echo "验证通过: $VERIFICATION_PASSED" >> "$REPORT_FILE"
echo "编译错误: $COMPILATION_ERRORS" >> "$REPORT_FILE"
echo >> "$REPORT_FILE"
echo "总运行时间 (平均 $RUN_COUNT 次运行)" >> "$REPORT_FILE"
echo "---------------------------" >> "$REPORT_FILE"
echo "SysY编译器: $(format_time $TOTAL_SYSY_TIME)" >> "$REPORT_FILE"
echo "GCC: $(format_time $TOTAL_GCC_TIME)" >> "$REPORT_FILE"
echo "总体性能比率(SysY/GCC): $total_ratio" >> "$REPORT_FILE"

# 打印汇总结果
echo "===== 性能测试完成 ====="
echo "测试总数: $TOTAL_TESTS"
echo "编译成功: $SUCCESSFUL_TESTS"
echo "验证通过: $VERIFICATION_PASSED ($(if $VERIFY_RESULTS; then echo "启用验证"; else echo "未验证"; fi))"
echo "编译错误: $COMPILATION_ERRORS"
echo ""
echo "总运行时间 (平均 $RUN_COUNT 次运行):"
echo "SysY编译器: $(format_time $TOTAL_SYSY_TIME)"
echo "GCC: $(format_time $TOTAL_GCC_TIME)"
echo "总体性能比率(SysY/GCC): $total_ratio"
echo ""
echo "详细报告已保存到 $REPORT_FILE"

exit 0
