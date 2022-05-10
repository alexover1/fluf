cmake_minimum_required (VERSION 3.8)
project(fluf)

# C++ version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(fluf
	src/app.cpp	
)

target_include_directories(fluf
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

# Needed for GLEW to work as a static library
if(MSVC)
  add_definitions(-DGLEW_STATIC)
endif()