# CMakeLists.txt (Root)

# 1. 升级版本号以匹配子项目 (Modern CMake 3.25+)
cmake_minimum_required (VERSION 3.25)

# 保持原本的 MSVC 调试配置优化 (热重载支持)
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# 定义整个解决方案的名字
project ("MiniCAM_Solution")

# 全局设定 C++ 标准 (这样子项目默认都会继承，不用每个都写一遍)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含子项目
#  注意顺序：先 Core 后 App
# 因为 App 依赖 Core，虽然 CMake 现代版本能自动处理依赖，但按逻辑顺序写是个好习惯
add_subdirectory ("Core")
add_subdirectory ("App")