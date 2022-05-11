cmake_minimum_required (VERSION 3.8)
project(fluf)

# C++ version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(fluf
	src/app.cpp	
	src/common.cpp
	src/time.cpp
	src/graphics.cpp
	src/drawing/shader.cpp
	src/drawing/sprite.cpp
	src/drawing/static_sprite.cpp
	src/drawing/batch.cpp
	src/drawing/simplerenderer.cpp
	src/internal/platform_glfw.cpp
	src/internal/platform_sdl2.cpp
	src/internal/renderer_opengl.cpp
)

option(FLUF_PLATFORM_SDL2 "Use SDL2 Platform Backend" ON)
option(FLUF_PLATFORM_GLFW "Use GLFW Platform Backend" OFF)
option(FLUF_RENDERER_OPENGL "Use OpenGL Renderer Backend" ON)

# Include dependiences
add_subdirectory(test)
add_subdirectory(libs/glfw)
add_subdirectory(libs/glew)
add_subdirectory(libs/sdl2)

# Use the GLFW Platform Backend
if (FLUF_PLATFORM_GLFW)
	add_compile_definitions(FLUF_PLATFORM_GLFW)
endif()

# Use the SDL2 Platform Backend
if (FLUF_PLATFORM_SDL2)
	add_compile_definitions(FLUF_PLATFORM_SDL2)
endif()

# Use the OpenGL Renderer Backend
if (FLUF_RENDERER_OPENGL)
	add_compile_definitions(FLUF_RENDERER_OPENGL)
endif()

target_include_directories(fluf
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(fluf PRIVATE libglew_static glfw SDL2main SDL2-static ${GLFW_LIBRARIES})

# Needed for GLEW to work as a static library
if(MSVC)
  add_definitions(-DGLEW_STATIC)
endif()