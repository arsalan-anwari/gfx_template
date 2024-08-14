cmake_minimum_required(VERSION 3.28.0)

project(gfx_template VERSION 0.1.0 LANGUAGES CXX CUDA)

# Define global build options 
option(SETTING_OPENGL_CUDA_CONTEXT "OpenGL window context using GLEW and GLFW with CUDA interop" OFF)
# option(ENABLE_FEATURE_B "Enable feature B" OFF)

set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# Apply global build settings based on system
include(cmake/ConfigureSettings.cmake)
include(cmake/ConfigureLibraries.cmake)

# Build C++23 modules
add_subdirectory(modules/types)
add_subdirectory(modules/gfx_canvas)
add_subdirectory(modules/gfx_window_manager)

# Build Examples
add_subdirectory(examples/window_manager)