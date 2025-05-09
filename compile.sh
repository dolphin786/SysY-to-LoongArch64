base_name=$(basename "$1" .sy)
asm_file="$base_name.S"
ll_file="$base_name.ll"
exe_file="$base_name.exe"


# 生成LoongArch64汇编代码
./build/sysyc "$1" -S "$asm_file" -i "$ll_file"


# 关键路径
SYSROOT="/opt/cross-tools/target"
GCC_LIB_PATH="/opt/cross-tools/lib/gcc/loongarch64-unknown-linux-gnu/13.0.0"


# 编译sylib.c、汇编代码，并链接，加了-g选项用于包含调试符号，同时设置了栈内存为100MB
clang-16 -g -target loongarch64-unknown-linux-gnu -mabi=lp64d --sysroot="$SYSROOT" -c sylib.c -o sylib.o \
        && clang-16 -g -target loongarch64-unknown-linux-gnu -mabi=lp64d --sysroot="$SYSROOT" -Wno-override-module -c "$asm_file" -o "${asm_file%.*}.o" \
        && clang-16 -g -target loongarch64-unknown-linux-gnu -mabi=lp64d -fuse-ld=bfd -static \
        --sysroot="$SYSROOT" \
        -L "$SYSROOT/usr/lib64" \
        -L "$GCC_LIB_PATH" \
        -Wl,-z,stack-size=104857600 \
        "${asm_file%.*}.o" sylib.o \
        -lgcc \
        -lc \
        "$SYSROOT/usr/lib64/crtn.o" \
        -o "$exe_file"