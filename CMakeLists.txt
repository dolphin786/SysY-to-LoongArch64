cmake_minimum_required(VERSION 3.15)  # 推荐最低 3.15 支持 C++17
project(sysyc)
# 设定 C++标准并禁用扩展
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
# 生成编译命令数据库（辅助 IDE 或工具分析）
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# 收集所有需编译的源文件
file(GLOB_RECURSE SOURCE_FILES
    "parser/generated/*.cpp"  # 收集生成的 ANTLR 代码
    "src/checker/*.cpp"
    "src/ir/*.cpp"
    "src/common/*.cpp"
    "src/asm/*.cpp"
    "sysyc.cpp"
)
# 定义可执行目标
add_executable(sysyc ${SOURCE_FILES})
# 添加头文件搜索路径（针对可执行目标 SysYIRGenerator）
target_include_directories(sysyc PRIVATE
    include       # 项目自有头文件
    parser/generated          # ANTLR 生成的头文件
    /usr/local/include/antlr4-runtime  # ANTLR 系统级头文件
)
# 链接 ANTLR 运行时库
target_link_libraries(sysyc PRIVATE antlr4-runtime)