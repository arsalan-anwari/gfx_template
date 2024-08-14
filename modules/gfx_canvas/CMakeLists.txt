# Declare the library as an interface library
add_library(gfx_canvas)

target_sources(gfx_canvas
  PUBLIC
    FILE_SET CXX_MODULES 
    FILES
        gfx_canvas.cppm
)

if(SETTING_OPENGL_CUDA_CONTEXT)
  target_link_libraries(gfx_canvas PUBLIC GLEW::GLEW CUDA::cudart)
endif()

