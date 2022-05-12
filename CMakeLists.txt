cmake_minimum_required (VERSION 3.8)
project(fluf)

# C++ version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(fluf
	src/app.cpp
	src/common.cpp
	src/containers/str.cpp
	src/drawing/shader.cpp
	src/drawing/vbuffer.cpp 
	src/drawing/ibuffer.cpp
	src/drawing/varray.cpp
	libs/glad/glad.c
 )

# Include dependiences
add_subdirectory(test)
add_subdirectory(libs/sdl2)

target_include_directories(fluf
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	libs/glad
	PRIVATE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(fluf PRIVATE SDL2main SDL2-static)