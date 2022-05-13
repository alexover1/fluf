cmake_minimum_required (VERSION 3.8)
project(fluf)

# C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(fluf
	src/app.cpp
	src/common.cpp
	src/containers/str.cpp
	src/drawing/shader.cpp
	src/drawing/vbuffer.cpp 
	src/drawing/ibuffer.cpp
	src/drawing/varray.cpp
	src/drawing/renderer.cpp
	src/drawing/texture.cpp
	src/third_party/glad/glad.c
	src/third_party/glad/glad.h
	src/third_party/glad/khrplatform.h
	src/third_party/stb/stb_image.cpp
	src/third_party/stb/stb_image.h
)

# Include dependiences
add_subdirectory(test)
add_subdirectory(libs/sdl2)

include_directories($<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/third_party>)

target_include_directories(fluf
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(fluf PRIVATE SDL2main SDL2-static)