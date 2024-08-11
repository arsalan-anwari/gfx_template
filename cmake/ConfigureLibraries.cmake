find_package(fmt REQUIRED)

if(SETTING_OPENGL_CUDA_CONTEXT)
  find_package(GLEW REQUIRED)
  find_package(nvapi REQUIRED)
  find_package(CUDAToolkit REQUIRED)
endif()