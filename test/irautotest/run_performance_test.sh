# #!/bin/bash

# # 配置路径
# PERF_TEST_DIR="performance_cases"
# TEMP_DIR="build/perf_tests"
# RESULTS_DIR="$TEMP_DIR/results"
# REPORT_FILE="$TEMP_DIR/performance_report.txt"
# mkdir -p "$TEMP_DIR" "$RESULTS_DIR"

# # 清空报告文件
# echo "SysY编译器性能对比测试报告" > "$REPORT_FILE"
# echo "============================" >> "$REPORT_FILE"
# echo "您的编译器 vs GCC -O0" >> "$REPORT_FILE"
# echo "" >> "$REPORT_FILE"
# echo "测试日期: $(date)" >> "$REPORT_FILE"
# echo "" >> "$REPORT_FILE"
# echo "性能统计 (单位: 微秒)" >> "$REPORT_FILE"
# echo "-------------------------" >> "$REPORT_FILE"
# printf "%-30s %-15s %-15s %-15s %-15s\n" "测试样例" "您的编译器" "GCC -O0" "差异(绝对值)" "比率(您/GCC)" >> "$REPORT_FILE"
# echo "" >> "$REPORT_FILE"

# # 调整系统栈限制
# original_soft=$(ulimit -Ss)

# # 定义恢复函数
# restore_stack_limit() {
#   echo "恢复原始栈限制..."
#   ulimit -Ss "$original_soft" 2>/dev/null || echo "恢复软限制失败（需要权限或超出硬限制）"
# }

# # 注册退出时的恢复操作
# trap restore_stack_limit EXIT

# # 设置临时栈限制为新值（1GB）
# new_limit=1048576  # 1024 * 1024 KB = 1GB
# echo "当前系统栈限制（ulimit -s）：$(ulimit -s) KB"
# echo "尝试设置临时栈限制为 $((new_limit / 1024)) MB..."
# if ! ulimit -Ss "$new_limit"; then
#   echo "错误：无法设置栈限制到 $new_limit KB"
#   exit 1
# fi

# # 定义关键路径
# SYSROOT="/opt/cross-tools/target"
# GCC_LIB_PATH="/opt/cross-tools/lib/gcc/loongarch64-unknown-linux-gnu/13.0.0"

# SYLIB_INCLUDE="-I."

# # 统计变量
# declare -i YOUR_TOTAL_TIME=0 GCC_TOTAL_TIME=0 VALID_TESTS=0 PASS=0 FAIL=0

# # 提取时间函数 (格式: TOTAL: XH-YM-ZS-Wus)
# extract_time_microseconds() {
#     local time_line="$1"
#     # 尝试匹配完整格式 XH-YM-ZS-Wus
#     if [[ "$time_line" =~ TOTAL:\ ([0-9]+)H-([0-9]+)M-([0-9]+)S-([0-9]+)us ]]; then
#         local hours="${BASH_REMATCH[1]}"
#         local minutes="${BASH_REMATCH[2]}"
#         local seconds="${BASH_REMATCH[3]}"
#         local microseconds="${BASH_REMATCH[4]}"
        
#         # 转换为微秒
#         echo $(( hours*3600000000 + minutes*60000000 + seconds*1000000 + microseconds ))
#     else
#         # 如果格式不匹配，返回0
#         echo "0"
#     fi
# }

# # 寻找测试样例
# find "$PERF_TEST_DIR" -name "*.sy" | sort | while read -r sy_file; do
#     # 生成基础名称
#     base_name=$(basename "$sy_file" .sy)
#     echo "-----------------------------------------"
#     echo "性能测试: $base_name"
    
#     # 提取相关文件路径
#     in_file="${sy_file%.sy}.in"
#     out_file="${sy_file%.sy}.out"
    
#     # 检查输出文件是否存在
#     if [ ! -f "$out_file" ]; then
#         echo "  ✗ 缺少输出文件 $out_file，跳过测试"
#         continue
#     fi
    
#     # 您的编译器相关文件
#     your_ll_file="$TEMP_DIR/${base_name}_your.ll"
#     your_exe_file="$TEMP_DIR/${base_name}_your.exe"
#     your_out_file="$RESULTS_DIR/${base_name}_your.out"
#     your_time_file="$RESULTS_DIR/${base_name}_your.time"
    
#     # GCC相关文件
#     gcc_exe_file="$TEMP_DIR/${base_name}_gcc.exe"
#     gcc_out_file="$RESULTS_DIR/${base_name}_gcc.out"
#     gcc_time_file="$RESULTS_DIR/${base_name}_gcc.time"
    
#     echo "  1. 编译测试样例..."
    
#     # 步骤1: 使用您的编译器生成LLVM IR
#     echo "    * 使用您的编译器..."
#     if ! ./build/SysYIRGeneratorAutoTester "$sy_file" "$your_ll_file" &>/dev/null; then
#         echo "    ✗ 您的编译器无法生成IR，跳过此测试案例"
#         ((FAIL++))
#         continue
#     fi
    
#     # 步骤2: 将您的IR编译为可执行文件
#     if ! clang-16 -g $SYLIB_INCLUDE -target loongarch64-unknown-linux-gnu -mabi=lp64d --sysroot="$SYSROOT" -c sylib.c -o sylib.o \
#         || ! clang-16 -g -target loongarch64-unknown-linux-gnu -mabi=lp64d --sysroot="$SYSROOT" -Wno-override-module -c "$your_ll_file" -S -o "${your_ll_file%.*}.s" \
#         || ! clang-16 -g -target loongarch64-unknown-linux-gnu -mabi=lp64d --sysroot="$SYSROOT" -Wno-override-module -c "$your_ll_file" -o "${your_ll_file%.*}.o" \
#         || ! clang-16 -g -target loongarch64-unknown-linux-gnu -mabi=lp64d -fuse-ld=bfd -static \
#         --sysroot="$SYSROOT" \
#         -L "$SYSROOT/usr/lib64" \
#         -L "$GCC_LIB_PATH" \
#         -Wl,-z,stack-size=104857600 \
#         "${your_ll_file%.*}.o" sylib.o \
#         -lgcc \
#         -lc \
#         "$SYSROOT/usr/lib64/crtn.o" \
#         -o "$your_exe_file"; then
#         echo "    ✗ 您的IR编译链接失败，跳过此测试案例"
#         ((FAIL++))
#         continue
#     fi
    
#     # 步骤3: 使用GCC -O0编译样例
#     echo "    * 使用GCC -O0..."
#     # 创建临时C文件 (复制.sy到.c)
#     # temp_c_file="$TEMP_DIR/${base_name}.c"
#     # cp "$sy_file" "$temp_c_file"

    
#     # 创建临时C文件 (复制.sy到.c并添加头文件包含)
#     temp_c_file="$TEMP_DIR/${base_name}.c"
#     echo '#include "sylib.h"' > "$temp_c_file"  # 首先添加头文件包含
#     cat "$sy_file" >> "$temp_c_file"            # 然后追加原始内容
    
#     # 使用GCC交叉编译
#     if ! loongarch64-unknown-linux-gnu-gcc -O0 $SYLIB_INCLUDE -static -o "$gcc_exe_file" "$temp_c_file" sylib.c -Wl,-z,stack-size=104857600 -fcommon; then
#         echo "    ✗ GCC编译失败，跳过此测试案例"
#         ((FAIL++))
#         continue
#     fi
    
#     echo "  2. 运行并验证测试样例..."
    
#     # 步骤4: 运行您的可执行文件
#     echo "    * 运行您的可执行文件..."
#     if [ -f "$in_file" ]; then
#         # 有输入文件的情况
#         qemu-loongarch64 "$your_exe_file" < "$in_file" > "$your_out_file" 2>&1
#     else
#         # 无输入文件的情况
#         qemu-loongarch64 "$your_exe_file" > "$your_out_file" 2>&1
#     fi
#     your_exit_code=$?
    
#     # 提取第一行(性能数据)并存储
#     head -n 1 "$your_out_file" > "$your_time_file"
#     # 删除第一行并添加退出码
#     sed -i '1d' "$your_out_file"
#     echo "" >> "$your_out_file"
#     echo "$your_exit_code" >> "$your_out_file"
    
#     # 步骤5: 运行GCC编译的可执行文件
#     echo "    * 运行GCC编译的可执行文件..."
#     if [ -f "$in_file" ]; then
#         # 有输入文件的情况
#         qemu-loongarch64 "$gcc_exe_file" < "$in_file" > "$gcc_out_file" 2>&1
#     else
#         # 无输入文件的情况
#         qemu-loongarch64 "$gcc_exe_file" > "$gcc_out_file" 2>&1
#     fi
#     gcc_exit_code=$?
    
#     # 提取第一行(性能数据)并存储
#     head -n 1 "$gcc_out_file" > "$gcc_time_file"
#     # 删除第一行并添加退出码
#     sed -i '1d' "$gcc_out_file"
#     echo "" >> "$gcc_out_file"
#     echo "$gcc_exit_code" >> "$gcc_out_file"
    
#     # 步骤6: 验证输出结果与预期输出一致
#     echo "  3. 验证输出结果..."
    
#     # 验证您编译器的输出
#     if ! diff -bB -q "$your_out_file" "$out_file" &>/dev/null; then
#         echo "    ✗ 您的编译器输出与预期不符"
#         ((FAIL++))
#         continue
#     fi
    
#     # 验证GCC的输出
#     if ! diff -bB -q "$gcc_out_file" "$out_file" &>/dev/null; then
#         echo "    ✗ GCC输出与预期不符"
#         ((FAIL++))
#         continue
#     fi
    
#     echo "    ✓ 两个编译器的输出都符合预期"
    
#     # 步骤7: 提取执行时间并计算性能差异
#     your_time_line=$(cat "$your_time_file")
#     gcc_time_line=$(cat "$gcc_time_file")
    
#     your_time=$(extract_time_microseconds "$your_time_line")
#     gcc_time=$(extract_time_microseconds "$gcc_time_line")
    
#     # 只处理成功提取时间的样例
#     if [ "$your_time" != "0" ] && [ "$gcc_time" != "0" ]; then
#         # 计算差异
#         time_diff=$((your_time - gcc_time))
#         abs_diff=${time_diff#-}  # 绝对值
        
#         # 计算比率 (保留两位小数)
#         ratio=$(echo "scale=2; $your_time / $gcc_time" | bc -l)
        
#         # 累加总时间
#         YOUR_TOTAL_TIME=$((YOUR_TOTAL_TIME + your_time))
#         GCC_TOTAL_TIME=$((GCC_TOTAL_TIME + gcc_time))
#         ((VALID_TESTS++))
        
#         # 输出性能对比
#         echo "  4. 性能对比:"
#         echo "    * 您的编译器: $your_time 微秒"
#         echo "    * GCC -O0: $gcc_time 微秒"
#         echo "    * 差异: $time_diff 微秒"
#         echo "    * 比率: $ratio"
        
#         # 将结果写入报告
#         printf "%-30s %-15d %-15d %-15d %-15.2f\n" "$base_name" "$your_time" "$gcc_time" "$abs_diff" "$ratio" >> "$REPORT_FILE"
        
#         ((PASS++))
#     else
#         echo "    ✗ 无法提取执行时间信息"
#         ((FAIL++))
#     fi
# done

# # 计算总体性能比
# if [ $VALID_TESTS -gt 0 ] && [ $GCC_TOTAL_TIME -gt 0 ]; then
#     OVERALL_RATIO=$(echo "scale=4; $YOUR_TOTAL_TIME / $GCC_TOTAL_TIME" | bc -l)
    
#     # 添加总结到报告
#     echo "" >> "$REPORT_FILE"
#     echo "总体性能统计" >> "$REPORT_FILE"
#     echo "-------------------------" >> "$REPORT_FILE"
#     echo "有效测试数: $VALID_TESTS" >> "$REPORT_FILE"
#     echo "您的编译器总执行时间: $YOUR_TOTAL_TIME 微秒" >> "$REPORT_FILE"
#     echo "GCC -O0总执行时间: $GCC_TOTAL_TIME 微秒" >> "$REPORT_FILE"
#     echo "总体性能比率(您/GCC): $OVERALL_RATIO" >> "$REPORT_FILE"
    
#     if (( $(echo "$OVERALL_RATIO < 1.0" | bc -l) )); then
#         percent_faster=$(echo "scale=2; (1.0 - $OVERALL_RATIO) * 100" | bc -l)
#         echo "您的编译器比GCC -O0快 $percent_faster%" >> "$REPORT_FILE"
#     else
#         percent_slower=$(echo "scale=2; ($OVERALL_RATIO - 1.0) * 100" | bc -l)
#         echo "您的编译器比GCC -O0慢 $percent_slower%" >> "$REPORT_FILE"
#     fi
    
#     # 控制台输出总结
#     echo "-----------------------------------------"
#     echo "性能测试完成"
#     echo "通过: $PASS  失败: $FAIL"
#     echo "总体性能比率(您/GCC): $OVERALL_RATIO"
    
#     if (( $(echo "$OVERALL_RATIO < 1.0" | bc -l) )); then
#         echo "您的编译器比GCC -O0快 $percent_faster%"
#     else
#         echo "您的编译器比GCC -O0慢 $percent_slower%"
#     fi
    
#     echo "详细报告已保存到: $REPORT_FILE"
# else
#     echo "没有足够的有效测试数据来计算总体性能比率"
# fi

# exit $((FAIL > 0 ? 1 : 0))




# 修改后的版本，将stderr和stdout分开输出，并提取timer进行比较

#!/bin/bash

# 配置路径
PERF_TEST_DIR="performance_cases"
TEMP_DIR="build/perf_tests"
RESULTS_DIR="$TEMP_DIR/results"
REPORT_FILE="$TEMP_DIR/performance_report.txt"
TIMER_REPORT_FILE="$TEMP_DIR/timer_performance_report.txt"
mkdir -p "$TEMP_DIR" "$RESULTS_DIR"

# 清空报告文件
echo "SysY编译器性能对比测试报告" > "$REPORT_FILE"
echo "============================" >> "$REPORT_FILE"
echo "您的编译器 vs GCC -O0" >> "$REPORT_FILE"
echo "" >> "$REPORT_FILE"
echo "测试日期: $(date)" >> "$REPORT_FILE"
echo "" >> "$REPORT_FILE"
echo "性能统计 (单位: 微秒)" >> "$REPORT_FILE"
echo "-------------------------" >> "$REPORT_FILE"
printf "%-30s %-15s %-15s %-15s %-15s\n" "测试样例" "您的编译器" "GCC -O0" "差异(绝对值)" "比率(您/GCC)" >> "$REPORT_FILE"
echo "" >> "$REPORT_FILE"

# Timer报告文件
echo "SysY编译器Timer性能对比测试报告" > "$TIMER_REPORT_FILE"
echo "============================" >> "$TIMER_REPORT_FILE"
echo "您的编译器 vs GCC -O0" >> "$TIMER_REPORT_FILE"
echo "" >> "$TIMER_REPORT_FILE"
echo "测试日期: $(date)" >> "$TIMER_REPORT_FILE"
echo "" >> "$TIMER_REPORT_FILE"
echo "Timer性能统计 (单位: 微秒)" >> "$TIMER_REPORT_FILE"

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

# 定义关键路径
SYSROOT="/opt/cross-tools/target"
GCC_LIB_PATH="/opt/cross-tools/lib/gcc/loongarch64-unknown-linux-gnu/13.0.0"

SYLIB_INCLUDE="-I."

# 统计变量
declare -i YOUR_TOTAL_TIME=0 GCC_TOTAL_TIME=0 VALID_TESTS=0 PASS=0 FAIL=0

# 提取时间函数 (格式: TOTAL: XH-YM-ZS-Wus)
extract_time_microseconds() {
    local time_line="$1"
    # 尝试匹配完整格式 XH-YM-ZS-Wus
    if [[ "$time_line" =~ TOTAL:\ ([0-9]+)H-([0-9]+)M-([0-9]+)S-([0-9]+)us ]]; then
        local hours="${BASH_REMATCH[1]}"
        local minutes="${BASH_REMATCH[2]}"
        local seconds="${BASH_REMATCH[3]}"
        local microseconds="${BASH_REMATCH[4]}"
        
        # 转换为微秒
        echo $(( hours*3600000000 + minutes*60000000 + seconds*1000000 + microseconds ))
    else
        # 如果格式不匹配，返回0
        echo "0"
    fi
}

# 将Timer时间字符串转换为微秒
# parse_timer_time() {
#     local time_str="$1"
#     local hours=$(echo "$time_str" | grep -oE "^[0-9]+" | head -1)
#     local minutes=$(echo "$time_str" | grep -oE "-[0-9]+M" | grep -oE "[0-9]+")
#     local seconds=$(echo "$time_str" | grep -oE "-[0-9]+S" | grep -oE "[0-9]+")
#     local microseconds=$(echo "$time_str" | grep -oE "-[0-9]+us" | grep -oE "[0-9]+")
    
#     echo $(( hours*3600000000 + minutes*60000000 + seconds*1000000 + microseconds ))
# }

parse_timer_time() {
    local time_str="$1"
    
    # 更精确的正则表达式，匹配各个时间组件
    local hours=$(echo "$time_str" | grep -oE "^[0-9]+H" | grep -oE "[0-9]+")
    local minutes=$(echo "$time_str" | grep -oE "[0-9]+M" | grep -oE "[0-9]+")
    local seconds=$(echo "$time_str" | grep -oE "[0-9]+S" | grep -oE "[0-9]+")
    local microseconds=$(echo "$time_str" | grep -oE "[0-9]+us" | grep -oE "[0-9]+")
    
    # 添加调试信息
    echo "DEBUG: 时间字符串: $time_str" >&2
    echo "DEBUG: 小时: $hours, 分钟: $minutes, 秒: $seconds, 微秒: $microseconds" >&2
    
    # 防止空值导致的计算错误
    hours=${hours:-0}
    minutes=${minutes:-0}
    seconds=${seconds:-0}
    microseconds=${microseconds:-0}
    
    # 计算总微秒数
    local total_us=$(( hours*3600000000 + minutes*60000000 + seconds*1000000 + microseconds ))
    echo "DEBUG: 总微秒数: $total_us" >&2
    
    echo "$total_us"
}

# 寻找测试样例
find "$PERF_TEST_DIR" -name "*.sy" | sort | while read -r sy_file; do
    # 生成基础名称
    base_name=$(basename "$sy_file" .sy)
    echo "-----------------------------------------"
    echo "性能测试: $base_name"
    
    # 提取相关文件路径
    in_file="${sy_file%.sy}.in"
    out_file="${sy_file%.sy}.out"
    
    # 检查输出文件是否存在
    if [ ! -f "$out_file" ]; then
        echo "  ✗ 缺少输出文件 $out_file，跳过测试"
        continue
    fi
    
    # 您的编译器相关文件
    your_ll_file="$TEMP_DIR/${base_name}_your.ll"
    your_exe_file="$TEMP_DIR/${base_name}_your.exe"
    your_out_file="$RESULTS_DIR/${base_name}_your.out"
    your_err_file="$RESULTS_DIR/${base_name}_your.err" # 新增错误输出文件
    your_time_file="$RESULTS_DIR/${base_name}_your.time"
    
    # GCC相关文件
    gcc_exe_file="$TEMP_DIR/${base_name}_gcc.exe"
    gcc_out_file="$RESULTS_DIR/${base_name}_gcc.out"
    gcc_err_file="$RESULTS_DIR/${base_name}_gcc.err" # 新增错误输出文件
    gcc_time_file="$RESULTS_DIR/${base_name}_gcc.time"
    
    echo "  1. 编译测试样例..."


    # 创建临时sy文件 (复制.sy到.c并添加头文件包含)
    temp_sy_file="$TEMP_DIR/${base_name}.sy"
    echo "" > "$temp_sy_file"  # 首先添加空行
    cat "$sy_file" >> "$temp_sy_file"            # 然后追加原始内容
    
    # 步骤1: 使用您的编译器生成LLVM IR
    echo "    * 使用您的编译器..."
    if ! ./build/SysYIRGeneratorAutoTester "$temp_sy_file" "$your_ll_file" &>/dev/null; then
        echo "    ✗ 您的编译器无法生成IR，跳过此测试案例"
        ((FAIL++))
        continue
    fi
    
    # 步骤2: 将您的IR编译为可执行文件
    if ! clang-16 -g $SYLIB_INCLUDE -target loongarch64-unknown-linux-gnu -mabi=lp64d --sysroot="$SYSROOT" -c sylib.c -o sylib.o \
        || ! clang-16 -g -target loongarch64-unknown-linux-gnu -mabi=lp64d --sysroot="$SYSROOT" -Wno-override-module -c "$your_ll_file" -S -o "${your_ll_file%.*}.s" \
        || ! clang-16 -g -target loongarch64-unknown-linux-gnu -mabi=lp64d --sysroot="$SYSROOT" -Wno-override-module -c "$your_ll_file" -o "${your_ll_file%.*}.o" \
        || ! clang-16 -g -target loongarch64-unknown-linux-gnu -mabi=lp64d -fuse-ld=bfd -static \
        --sysroot="$SYSROOT" \
        -L "$SYSROOT/usr/lib64" \
        -L "$GCC_LIB_PATH" \
        -Wl,-z,stack-size=104857600 \
        "${your_ll_file%.*}.o" sylib.o \
        -lgcc \
        -lc \
        "$SYSROOT/usr/lib64/crtn.o" \
        -o "$your_exe_file"; then
        echo "    ✗ 您的IR编译链接失败，跳过此测试案例"
        ((FAIL++))
        continue
    fi
    
    # 步骤3: 使用GCC -O0编译样例
    echo "    * 使用GCC -O0..."
    # 创建临时C文件 (复制.sy到.c并添加头文件包含)
    temp_c_file="$TEMP_DIR/${base_name}.c"
    echo '#include "sylib.h"' > "$temp_c_file"  # 首先添加头文件包含
    cat "$sy_file" >> "$temp_c_file"            # 然后追加原始内容
    
    # 使用GCC交叉编译
    if ! loongarch64-unknown-linux-gnu-gcc -O0 $SYLIB_INCLUDE -static -o "$gcc_exe_file" "$temp_c_file" sylib.c -Wl,-z,stack-size=104857600 -fcommon; then
        echo "    ✗ GCC编译失败，跳过此测试案例"
        ((FAIL++))
        continue
    fi
    
    echo "  2. 运行并验证测试样例..."
    
    # 步骤4: 运行您的可执行文件
    echo "    * 运行您的可执行文件..."
    if [ -f "$in_file" ]; then
        # 有输入文件的情况
        qemu-loongarch64 "$your_exe_file" < "$in_file" > "$your_out_file" 2> "$your_err_file"
    else
        # 无输入文件的情况
        qemu-loongarch64 "$your_exe_file" > "$your_out_file" 2> "$your_err_file"
    fi
    your_exit_code=$?
    
    # # 提取第一行(性能数据)并存储
    # head -n 1 "$your_out_file" > "$your_time_file"
    # # 删除第一行并添加退出码
    # sed -i '1d' "$your_out_file"
    echo "" >> "$your_out_file"
    echo "$your_exit_code" >> "$your_out_file"
    
    # 步骤5: 运行GCC编译的可执行文件
    echo "    * 运行GCC编译的可执行文件..."
    if [ -f "$in_file" ]; then
        # 有输入文件的情况
        qemu-loongarch64 "$gcc_exe_file" < "$in_file" > "$gcc_out_file" 2> "$gcc_err_file"
    else
        # 无输入文件的情况
        qemu-loongarch64 "$gcc_exe_file" > "$gcc_out_file" 2> "$gcc_err_file"
    fi
    gcc_exit_code=$?
    
    # # 提取第一行(性能数据)并存储
    # head -n 1 "$gcc_out_file" > "$gcc_time_file"
    # # 删除第一行并添加退出码
    # sed -i '1d' "$gcc_out_file"
    echo "" >> "$gcc_out_file"
    echo "$gcc_exit_code" >> "$gcc_out_file"
    
    # 步骤6: 验证输出结果与预期输出一致
    echo "  3. 验证输出结果..."
    
    # 验证您编译器的输出
    if ! diff -bB -q "$your_out_file" "$out_file" &>/dev/null; then
        echo "    ✗ 您的编译器输出与预期不符"
        ((FAIL++))
        continue
    fi
    
    # 验证GCC的输出
    if ! diff -bB -q "$gcc_out_file" "$out_file" &>/dev/null; then
        echo "    ✗ GCC输出与预期不符"
        ((FAIL++))
        continue
    fi
    
    echo "    ✓ 两个编译器的输出都符合预期"
    
    # # 步骤7: 提取执行时间并计算性能差异
    # your_time_line=$(cat "$your_time_file")
    # gcc_time_line=$(cat "$gcc_time_file")
    
    # your_time=$(extract_time_microseconds "$your_time_line")
    # gcc_time=$(extract_time_microseconds "$gcc_time_line")
    
    # # 只处理成功提取时间的样例
    # if [ "$your_time" != "0" ] && [ "$gcc_time" != "0" ]; then
    #     # 计算差异
    #     time_diff=$((your_time - gcc_time))
    #     abs_diff=${time_diff#-}  # 绝对值
        
    #     # 计算比率 (保留两位小数)
    #     ratio=$(echo "scale=2; $your_time / $gcc_time" | bc -l)
        
    #     # 累加总时间
    #     YOUR_TOTAL_TIME=$((YOUR_TOTAL_TIME + your_time))
    #     GCC_TOTAL_TIME=$((GCC_TOTAL_TIME + gcc_time))
    #     ((VALID_TESTS++))
        
    #     # 输出性能对比
    #     echo "  4. 性能对比:"
    #     echo "    * 您的编译器: $your_time 微秒"
    #     echo "    * GCC -O0: $gcc_time 微秒"
    #     echo "    * 差异: $time_diff 微秒"
    #     echo "    * 比率: $ratio"
        
    #     # 将结果写入报告
    #     printf "%-30s %-15d %-15d %-15d %-15.2f\n" "$base_name" "$your_time" "$gcc_time" "$abs_diff" "$ratio" >> "$REPORT_FILE"
        
    #     ((PASS++))
    # else
    #     echo "    ✗ 无法提取执行时间信息"
    #     ((FAIL++))
    # fi
    




    # 步骤8: 提取并比较Timer信息 (新增部分)
    # echo "  4. Timer性能对比:"
    # echo "-------------------------" >> "$TIMER_REPORT_FILE"
    # echo "测试样例: $base_name" >> "$TIMER_REPORT_FILE"
    # echo "-------------------------" >> "$TIMER_REPORT_FILE"
    
    # # 提取Timer行
    # grep -E "^Timer@" "$your_err_file" > "$RESULTS_DIR/${base_name}_your_timers.txt"
    # grep -E "^Timer@" "$gcc_err_file" > "$RESULTS_DIR/${base_name}_gcc_timers.txt"
    
    # # 如果存在Timer信息，则分析并比较
    # if [ -s "$RESULTS_DIR/${base_name}_your_timers.txt" ] && [ -s "$RESULTS_DIR/${base_name}_gcc_timers.txt" ]; then
    #     printf "%-20s %-15s %-15s %-15s %-15s\n" "Timer ID" "您的编译器" "GCC -O0" "差异(绝对值)" "比率(您/GCC)" >> "$TIMER_REPORT_FILE"
    #     # echo "1111"
    #     # 读取您的编译器的Timer信息
    #     while IFS= read -r your_timer_line; do
    #         # 提取Timer ID和时间
    #         timer_id=$(echo "$your_timer_line" | grep -oE "Timer@[0-9]+-[0-9]+")
    #         your_timer_time=$(echo "$your_timer_line" | grep -oE "[0-9]+H-[0-9]+M-[0-9]+S-[0-9]+us")
            
    #         if [[ ! -z "$timer_id" && ! -z "$your_timer_time" ]]; then
    #             # 在GCC输出中查找相同的Timer ID
    #             gcc_timer_line=$(grep "$timer_id" "$RESULTS_DIR/${base_name}_gcc_timers.txt")
    #             gcc_timer_time=$(echo "$gcc_timer_line" | grep -oE "[0-9]+H-[0-9]+M-[0-9]+S-[0-9]+us")
                
    #             if [[ ! -z "$gcc_timer_time" ]]; then
    #                 # 转换为微秒
    #                 your_timer_us=$(parse_timer_time "$your_timer_time")
    #                 gcc_timer_us=$(parse_timer_time "$gcc_timer_time")
                    
    #                 # 计算差异
    #                 timer_diff=$((your_timer_us - gcc_timer_us))
    #                 timer_abs_diff=${timer_diff#-}  # 绝对值
                    
    #                 # 计算比率 (保留两位小数)
    #                 if [ "$gcc_timer_us" != "0" ]; then
    #                     timer_ratio=$(echo "scale=2; $your_timer_us / $gcc_timer_us" | bc -l)
                        
    #                     # 输出到控制台
    #                     echo "    * $timer_id: 您 $your_timer_time vs GCC $gcc_timer_time (比率: $timer_ratio)"
                        
    #                     # 写入报告
    #                     printf "%-20s %-15d %-15d %-15d %-15.2f\n" "$timer_id" "$your_timer_us" "$gcc_timer_us" "$timer_abs_diff" "$timer_ratio" >> "$TIMER_REPORT_FILE"
    #                 else
    #                     echo "    * $timer_id: 您 $your_timer_time vs GCC $gcc_timer_time (GCC时间为0，无法计算比率)"
    #                     printf "%-20s %-15d %-15d %-15d %-15s\n" "$timer_id" "$your_timer_us" "$gcc_timer_us" "$timer_abs_diff" "N/A" >> "$TIMER_REPORT_FILE"
    #                 fi
    #             fi
    #         fi
    #     done < "$RESULTS_DIR/${base_name}_your_timers.txt"
        
    #     echo "" >> "$TIMER_REPORT_FILE"
    # else
    #     echo "    未找到Timer信息" 
    #     echo "未找到Timer信息" >> "$TIMER_REPORT_FILE"
    #     echo "" >> "$TIMER_REPORT_FILE"
    # fi






    # 步骤7: 提取并比较Timer信息
    echo "  4. Timer性能对比:"
    echo "-------------------------" >> "$TIMER_REPORT_FILE"
    echo "测试样例: $base_name" >> "$TIMER_REPORT_FILE"
    echo "-------------------------" >> "$TIMER_REPORT_FILE"
    
    # 提取Timer行
    grep -E "^Timer@" "$your_err_file" > "$RESULTS_DIR/${base_name}_your_timers.txt"
    grep -E "^Timer@" "$gcc_err_file" > "$RESULTS_DIR/${base_name}_gcc_timers.txt"
    
    # 如果存在Timer信息，则分析并比较
    if [ -s "$RESULTS_DIR/${base_name}_your_timers.txt" ] && [ -s "$RESULTS_DIR/${base_name}_gcc_timers.txt" ]; then
        printf "%-20s %-15s %-15s %-15s %-15s\n" "Timer ID" "您的编译器" "GCC -O0" "差异(绝对值)" "比率(您/GCC)" >> "$TIMER_REPORT_FILE"
        
        # 读取您的编译器的Timer信息
        while IFS= read -r your_timer_line; do
            # 提取Timer ID和时间
            timer_id=$(echo "$your_timer_line" | grep -oE "Timer@[0-9]+-[0-9]+")
            your_timer_time=$(echo "$your_timer_line" | grep -oE "[0-9]+H-[0-9]+M-[0-9]+S-[0-9]+us")

            echo "111"
            
            if [[ ! -z "$timer_id" && ! -z "$your_timer_time" ]]; then
                # 在GCC输出中查找相同的Timer ID
                gcc_timer_line=$(grep "$timer_id" "$RESULTS_DIR/${base_name}_gcc_timers.txt")
                gcc_timer_time=$(echo "$gcc_timer_line" | grep -oE "[0-9]+H-[0-9]+M-[0-9]+S-[0-9]+us")
                
                echo "2222 $gcc_timer_time"
                if [[ ! -z "$gcc_timer_time" ]]; then
                    # 转换为微秒
                    your_timer_us=$(parse_timer_time "$your_timer_time")
                    gcc_timer_us=$(parse_timer_time "$gcc_timer_time")
                    
                    # 计算差异
                    timer_diff=$((your_timer_us - gcc_timer_us))
                    timer_abs_diff=${timer_diff#-}  # 绝对值
                    
                    echo "33333 $your_timer_us $gcc_timer_us "
                    # 计算比率 (保留两位小数)
                    if [ "$gcc_timer_us" != "0" ]; then
                        timer_ratio=$(echo "scale=2; $your_timer_us / $gcc_timer_us" | bc -l)
                        
                        # 输出到控制台
                        echo "    * $timer_id: 您 $your_timer_time vs GCC $gcc_timer_time (比率: $timer_ratio)"
                        
                        # 写入报告
                        printf "%-20s %-15d %-15d %-15d %-15.2f\n" "$timer_id" "$your_timer_us" "$gcc_timer_us" "$timer_abs_diff" "$timer_ratio" >> "$TIMER_REPORT_FILE"
                    else
                        echo "    * $timer_id: 您 $your_timer_time vs GCC $gcc_timer_time (GCC时间为0，无法计算比率)"
                        printf "%-20s %-15d %-15d %-15d %-15s\n" "$timer_id" "$your_timer_us" "$gcc_timer_us" "$timer_abs_diff" "N/A" >> "$TIMER_REPORT_FILE"
                    fi
                fi
            fi
        done < "$RESULTS_DIR/${base_name}_your_timers.txt"
        
        echo "" >> "$TIMER_REPORT_FILE"
    else
        echo "    未找到Timer信息" 
        echo "未找到Timer信息" >> "$TIMER_REPORT_FILE"
        echo "" >> "$TIMER_REPORT_FILE"
    fi


done

# 计算总体性能比
if [ $VALID_TESTS -gt 0 ] && [ $GCC_TOTAL_TIME -gt 0 ]; then
    OVERALL_RATIO=$(echo "scale=4; $YOUR_TOTAL_TIME / $GCC_TOTAL_TIME" | bc -l)
    
    # 添加总结到报告
    echo "" >> "$REPORT_FILE"
    echo "总体性能统计" >> "$REPORT_FILE"
    echo "-------------------------" >> "$REPORT_FILE"
    echo "有效测试数: $VALID_TESTS" >> "$REPORT_FILE"
    echo "您的编译器总执行时间: $YOUR_TOTAL_TIME 微秒" >> "$REPORT_FILE"
    echo "GCC -O0总执行时间: $GCC_TOTAL_TIME 微秒" >> "$REPORT_FILE"
    echo "总体性能比率(您/GCC): $OVERALL_RATIO" >> "$REPORT_FILE"
    
    if (( $(echo "$OVERALL_RATIO < 1.0" | bc -l) )); then
        percent_faster=$(echo "scale=2; (1.0 - $OVERALL_RATIO) * 100" | bc -l)
        echo "您的编译器比GCC -O0快 $percent_faster%" >> "$REPORT_FILE"
    else
        percent_slower=$(echo "scale=2; ($OVERALL_RATIO - 1.0) * 100" | bc -l)
        echo "您的编译器比GCC -O0慢 $percent_slower%" >> "$REPORT_FILE"
    fi
    
    # 控制台输出总结
    echo "-----------------------------------------"
    echo "性能测试完成"
    echo "通过: $PASS  失败: $FAIL"
    echo "总体性能比率(您/GCC): $OVERALL_RATIO"
    
    if (( $(echo "$OVERALL_RATIO < 1.0" | bc -l) )); then
        echo "您的编译器比GCC -O0快 $percent_faster%"
    else
        echo "您的编译器比GCC -O0慢 $percent_slower%"
    fi
    
    echo "详细报告已保存到: $REPORT_FILE"
    echo "Timer详细报告已保存到: $TIMER_REPORT_FILE"
else
    echo "没有足够的有效测试数据来计算总体性能比率"
fi

exit $((FAIL > 0 ? 1 : 0))
