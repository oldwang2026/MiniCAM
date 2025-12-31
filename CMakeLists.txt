# CMakeLists.txt: 顶层 CMake 项目文件

# 1. 最低版本
cmake_minimum_required (VERSION 3.25)

# 2. MSVC 热重载支持 (保留你原有的配置，这对调试很有用)
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# 3. 定义解决方案名称
project ("MiniCAM_Solution")

# 1. 【exe 和 dll】去 bin
# Windows 运行程序时，去哪里找 exe，就去哪里找 dll。它俩必须在同一个屋檐下。
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 2. 【lib (静态库 + 导入库)】去 lib
# 这些是给 Linker (链接器) 用的，运行时不需要。
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


# 4. 包含子项目
add_subdirectory ("Core")