add_library(gfx_context)

target_sources(gfx_context
  PUBLIC
    FILE_SET CXX_MODULES FILES
        gfx_context.cppm
)

if(SETTING_OPENGL_WINDOW_CONTEXT)
  target_link_libraries(gfx_context PUBLIC glfw GLEW::GLEW)
endif()