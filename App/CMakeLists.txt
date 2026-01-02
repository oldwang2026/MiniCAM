
cmake_minimum_required (VERSION 3.25)

project("MiniCAM_Executable")

add_executable(MiniCAM)

target_sources(MiniCAM PRIVATE "main.cpp")

target_compile_definitions(MiniCAM 
    PRIVATE 
    PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}"
)

target_link_libraries(MiniCAM 
	PRIVATE
		MiniCAM_Core
)
