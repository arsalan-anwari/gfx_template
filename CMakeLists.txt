cmake_minimum_required(VERSION 3.10)
project(opengl_template VERSION 0.1.0 LANGUAGES C CXX)

find_package(fmt CONFIG REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(opengl_template main.cpp)

target_link_libraries(opengl_template PRIVATE fmt::fmt glfw GLEW::GLEW)

