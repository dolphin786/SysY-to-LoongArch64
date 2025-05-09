#!/bin/bash

# 安全清空 generated/ 目录
if [ -d "generated" ]; then
    echo "正在清理 generated/ 目录..."
    rm -rf generated/*
else
    echo "创建 generated/ 目录..."
    mkdir generated
fi

# 执行 ANTLR 生成命令
echo "开始生成词法/语法分析器代码..."

# java -jar ~/antlr/antlr-4.9.3-complete.jar SysYLex.g4 SysY.g4 -Dlanguage=Cpp -listener -visitor -o generated/

java -jar ~/antlr/antlr-4.9.3-complete.jar SysY.g4 -Dlanguage=Cpp -listener -visitor -o generated/

# 检查是否成功
if [ $? -eq 0 ]; then
    echo "代码生成成功！生成文件位于 generated/ 目录"
else
    echo "代码生成失败，请检查错误信息"
    exit 1
fi
