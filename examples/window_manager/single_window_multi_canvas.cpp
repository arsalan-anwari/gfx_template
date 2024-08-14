#include <GL/glew.h>
#include <cmath>
#include <exception>
#include <iostream>

 import types;
 import gfx_canvas;
 import gfx_window_manager;

 int main() {

     constexpr gfx_canvas_settings default_canvas_settings = {
        gfx_canvas_dim{ 800, 600 },
        "Demo of Single Window with multiple canvas",
        30, 2
     };

     try {
         auto demo_single_window_multi_canvas = gfx_window_manager<gfx_api::opengl>(
             gfx_canvas_render_mode::single_window_multi_canvas,
             {
                 gfx_canvas<gfx_api::opengl>{ default_canvas_settings, []() {
                 // Render a triangle
                 glBegin(GL_TRIANGLES);
                 glVertex2f(-0.5f, -0.5f);
                 glVertex2f(0.5f, -0.5f);
                 glVertex2f(0.0f, 0.5f);
                 glEnd();
             } },

             gfx_canvas<gfx_api::opengl>{ default_canvas_settings, []() {
                 // Render a square
                 glBegin(GL_QUADS);
                 glVertex2f(-0.5f, -0.5f);
                 glVertex2f(0.5f, -0.5f);
                 glVertex2f(0.5f, 0.5f);
                 glVertex2f(-0.5f, 0.5f);
                 glEnd();
             } },

             gfx_canvas<gfx_api::opengl>{ default_canvas_settings, []() {
                // Render a circle
                glBegin(GL_POLYGON);
                constexpr i32 segments = 100;
                constexpr f32 radius = 0.5f;
                for (int i = 0; i < segments; ++i) {
                    f32 theta = 2.0f * 3.1415926f * static_cast<f32>(i) / static_cast<f32>(segments);
                    f32 x = radius * cosf(theta);
                    f32 y = radius * sinf(theta);
                    glVertex2f(x, y);
                }
                glEnd();
             } }

             }
         );


         demo_single_window_multi_canvas.start();

     }
     catch (const std::exception& e) {
         std::cout << e.what() << std::endl;
     }


     return 0;
 
 }