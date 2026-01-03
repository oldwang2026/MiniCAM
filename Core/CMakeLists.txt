# Core/CMakeLists.txt
cmake_minimum_required (VERSION 3.25) # 必须升级最低版本

project ("MiniCAM_Core_Lib")

# 1. 创建静态库
add_library(MiniCAM_Core STATIC)

# 2. 添加源文件 & 定义头文件集 (核心改动!)
target_sources(MiniCAM_Core

    PRIVATE
        "src/STLReader.cpp"
        "src/BoundingBox.cpp"
        "src/Part.cpp"


    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "include"    # 指定头文件的根目录
        FILES
            "include/STLReader.h"
            "include/GeoTypes.h"
            "include/BoundingBox.h"
            "include/Part.h"
            
 )

# 3. 设置 C++ 标准
target_compile_features(MiniCAM_Core PUBLIC cxx_std_20)

target_include_directories(MiniCAM_Core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include") 