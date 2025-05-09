#!/bin/bash
# 增量编译+按需完整重建脚本
# Usage: 
#   ./autotest.sh       -> 增量编译（默认）
#   ./autotest.sh --clean -> 清理并全量重建
# 1. 处理参数
if [ "$1" == "--clean" ]; then
    echo "[INFO] 清理旧构建..."
    rm -rf build
fi
# 2. 确保构建目录存在
mkdir -p build
# 3. 生成构建系统（仅在首次或 --clean 后重新配置）
if [ ! -f "build/CMakeCache.txt" ] || [ "$1" == "--clean" ]; then
    echo "[INFO] 生成 CMake 构建系统..."
    cmake -S . -B build
fi
# 4. 增量编译
echo "[INFO] 开始编译..."
cmake --build build --parallel $(nproc)  # 启用多线程加速