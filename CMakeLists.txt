cmake_minimum_required(VERSION 3.28.0)
project(opengl_template VERSION 0.1.0 LANGUAGES C CXX)

# find_package(glfw3 REQUIRED)
# find_package(GLEW REQUIRED)

# target_link_libraries(opengl_template PRIVATE glfw GLEW::GLEW)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(modules/gfx_context)
add_subdirectory(examples/hello_world)