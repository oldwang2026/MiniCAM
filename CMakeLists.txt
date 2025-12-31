# CMakeLists.txt: 顶层 CMake 项目文件

# 1. 提升最低版本
# C++20 的完美支持建议使用 3.12+，这里用 3.20 比较稳妥
cmake_minimum_required (VERSION 3.20)

# 2. MSVC 热重载支持 (保留你原有的配置，这对调试很有用)
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# 3. 定义解决方案名称
project ("MiniCAM_Solution")

# =========================================================
# 关键改进：统一输出目录 (Output Directories)
# =========================================================
# 这一步是为了让所有的 exe, dll, lib 都生成到同一个地方 (比如 build/bin)
# 这样你的 exe 就能自动找到同目录下的 dll，无需手动复制！

# .lib 静态库去 build/lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# .dll 动态库去 build/bin
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# .exe 可执行文件去 build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# 4. 包含子项目
add_subdirectory ("Core")