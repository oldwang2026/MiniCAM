# CMakeLists.txt

# 1. 定义项目
project("MiniCAM_Executable" VERSION 1.0)

# 2. 创建可执行文件目标 (先定义一个目标)
add_executable(MiniCAM)

# 3. 为目标添加源文件和头文件 (Modern CMake 推荐方式)
# 使用 PRIVATE 表示这些文件仅用于构建 MiniCAM 自身
target_sources(MiniCAM PRIVATE
    "src/main.cpp"
    "src/STLReader.cpp"
    "include/STLReader.h"
    "include/GeoTypes.h"
)

# 4. 指定头文件搜索路径
# 使用 PRIVATE 确保路径只对 MiniCAM 目标有效
# "include" 是存放 .h 文件的目录
target_include_directories(MiniCAM PRIVATE "include")

# 5. 设置 C++ 标准 (推荐方式)
# 这样写 CMake 会自动处理版本要求，不需要写 if 判断
target_compile_features(MiniCAM PRIVATE cxx_std_20)

# 如果你希望在编译时强制要求支持 C++20，可以加上这两行：
set_target_properties(MiniCAM PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)