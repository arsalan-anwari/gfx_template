# Declare the library as an interface library
add_library(gfx_context)

target_sources(gfx_context
  PUBLIC
    FILE_SET CXX_MODULES 
    FILES
        gfx_context.cppm
)

if(SETTING_OPENGL_CUDA_CONTEXT)
  target_link_libraries(gfx_context PUBLIC fmt::fmt GLEW::GLEW nvapi::nvapi CUDA::cudart)
endif()
