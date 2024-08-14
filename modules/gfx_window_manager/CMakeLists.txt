# Declare the library as an interface library
add_library(gfx_window_manager)

target_sources(gfx_window_manager
  PUBLIC
    FILE_SET CXX_MODULES 
    FILES
        gfx_window_manager.cppm
)

if(SETTING_OPENGL_CUDA_CONTEXT)
  target_link_libraries(gfx_window_manager PUBLIC gfx_canvas glfw)
endif()
