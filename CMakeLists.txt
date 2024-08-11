cmake_minimum_required(VERSION 3.28.0)
project(gfx_template VERSION 0.1.0 LANGUAGES C CXX)

option(SETTING_OPENGL_CUDA_CONTEXT "OpenGL window context using GLEW and GLFW with CUDA binding using shared textures" OFF)
# option(ENABLE_FEATURE_B "Enable feature B" OFF)

include(cmake/ConfigureSettings.cmake)
include(cmake/ConfigureLibraries.cmake)

add_subdirectory(modules/gfx_context)
add_subdirectory(examples/hello_window)