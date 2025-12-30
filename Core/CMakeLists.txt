# CMakeList.txt: MIniCamCore 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

# 将源代码添加到此项目的可执行文件。
# Core/CMakeLists.txt

# 1. 定义这个子项目的名字 (生成的可执行文件就叫 MiniCAM.exe)
project ("MiniCAM_Executable")

# 2. 告诉 CMake 头文件在哪里 (相对于当前 Core 文件夹)
include_directories("include")

# 3. 收集源文件
set(SOURCES "src/main.cpp")

# 4. 生成可执行文件
# 注意：生成的 exe 会放在 out/build/.../Core/ 下面
add_executable (MiniCAM ${SOURCES})

# TODO: 如有需要，请添加测试并安装目标。
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MiniCAM PROPERTY CXX_STANDARD 20)
endif()


