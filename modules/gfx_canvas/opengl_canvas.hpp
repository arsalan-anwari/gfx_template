#pragma once

#include <mutex>
#include <GL/glew.h> // include GLEW and new version of GL on Windows

#include "../types/gfx_types.hpp"
#include "../types/exceptions_types.hpp"

struct opengl_canvas{

    static void init(){
        static std::once_flag flag;
        std::call_once(flag, [](){
            if (glewInit() != GLEW_OK) {
                throw std::system_error(ENOTSUP, std::system_category(), "[opengl_canvas] : Could not initialize GLEW!");    
            }
        });
    }

    void clear() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

};


template<> struct gfx_canvas_t<gfx_api_t::opengl>{
    using type = opengl_canvas;
};