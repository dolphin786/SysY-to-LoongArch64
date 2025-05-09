cmake_minimum_required(VERSION 3.15)
project(SysYAsmAutoTester)  # 修改项目名称以区分
# 配置基础编译选项
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# 获取项目根目录相对路径（重要！）
set(PROJECT_ROOT_DIR "../../")  # 因为CMakeLists现在在test/asmautotest下
# 收集源代码文件（使用修正后的路径）
file(GLOB_RECURSE SOURCE_FILES
    "${PROJECT_ROOT_DIR}parser/generated/*.cpp"  # Corrected path
    "${PROJECT_ROOT_DIR}src/checker/*.cpp"
    "${PROJECT_ROOT_DIR}src/ir/*.cpp"
    "${PROJECT_ROOT_DIR}src/common/*.cpp"
    "${PROJECT_ROOT_DIR}src/asm/*.cpp"
    "main.cpp"  # 当前目录下的主程序
)
# 定义可执行目标
add_executable(SysYAsmAutoTester ${SOURCE_FILES})  # 改名以区分原生成器
# 包含目录配置
target_include_directories(SysYAsmAutoTester PRIVATE
    "${PROJECT_ROOT_DIR}include"             # 根目录下的include
    "${PROJECT_ROOT_DIR}parser/generated"    # ANTLR生成目录
    "/usr/local/include/antlr4-runtime"      # 系统头文件仍用绝对路径
)
# 链接ANTLR库
target_link_libraries(SysYAsmAutoTester PRIVATE antlr4-runtime)