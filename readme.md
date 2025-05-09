# SysY-to-LoongArch64
## 介绍
一个由C++17编写的基于ANTLR4前端的编译器，可以将SysY2022语言编译为LoongArch64汇编，支持导出可读形式的LLVM IR。**项目参考的开源项目已在源码使用处标记。**
## 基础环境
* ANTLR4 C++运行时库 4.9.3， 安装在/usr/local
## 构建
```
bash ./build.sh --clean
```
在项目根目录输入上述命令，需要CMake 3.15及以上版本。
## 如何使用
```
build/sysyc example.sy -S example.S -i debug.ll
```
构建完成后，输入上述命令，将example.sy编译为LoongArch64汇编example.S的同时，导出未优化的LLVM IR文件debug.ll。
### 汇编与链接SysY运行时库
若要进一步得到可执行程序，example.S汇编后还需要链接SysY运行时库sylib.o，sylib.o由sylib.c编译得到。
也可以使用项目根目录下的脚本compile.sh，通过clang16汇编与静态链接得到可执行程序，该脚本需要/opt/cross-tool下的LoongArch交叉编译工具链（将<https://github.com/loongson/build-tools/releases/download/2022.09.06/loongarch64-clfs-6.3-cross-tools-gcc_and_clang-full.tar.xz>解压到/opt下得到）。
### 测试编译器
需要安装qemu-loongarch64用户模式，以及Clang16和LoongArch交叉编译工具链。
* 在test/autotest/下运行loongarch64_build_and_run_tests.sh使用functional_cases（来自<https://gitlab.eduxiji.net/csc1/nscscc/compiler2023/-/tree/master/%E5%85%AC%E5%BC%80%E6%A0%B7%E4%BE%8B%E4%B8%8E%E8%BF%90%E8%A1%8C%E6%97%B6%E5%BA%93/functional>）进行自动功能测试
* 在test/autotest/下运行loongarch64_build_and_run_diff_test进行差分功能测试，使用generate_sysy_test.py生成随机样例
* 在test/autotest/下运行run_perf_test.sh使用perf_test_cases进行性能测试，需要LoongArch交叉编译工具链中的loongarch64-unknown-linux-gnu-gcc，会在该目录下生成一份性能报告performance_report.txt
