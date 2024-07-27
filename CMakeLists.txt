cmake_minimum_required(VERSION 3.28.0)
project(gfx_template VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SETTING_OPENGL_WINDOW_CONTEXT "OpenGL window context using GLEW and GLFW" OFF)
# option(ENABLE_FEATURE_B "Enable feature B" OFF)

include(cmake/ConfigureSettings.cmake)
include(cmake/ConfigureLibraries.cmake)

add_subdirectory(modules/gfx_context)
add_subdirectory(examples/hello_window)