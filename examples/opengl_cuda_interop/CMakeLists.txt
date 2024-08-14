add_executable(opengl_cuda_interop opengl_cuda_interop.cpp)

add_library(cuda_kernel STATIC kernel.cu)

add_library(cxx_kernel_module)

target_sources(cxx_kernel_module
  PUBLIC
    FILE_SET CXX_MODULES 
    FILES
      kernel.cppm
)

target_link_libraries(cuda_kernel PUBLIC CUDA::cudart)

target_link_libraries(cxx_kernel_module PUBLIC GLEW::GLEW glfw cuda_kernel)

target_link_libraries(opengl_cuda_interop PUBLIC cxx_kernel_module)