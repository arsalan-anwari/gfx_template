// #include <GL/glew.h>

// import types;
// import gfx_canvas;
// import gfx_window;

// int main() {

//     auto opengl_window = gfx_window<gfx_os::windows, gfx_api::opengl, gfx_vendor::nvidia>(
//         gfx_window_settings{ 800, 600 },
//         {
//             gfx_canvas<gfx_api::opengl>{ [](){
//                 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//                 GLfloat vertices[] = {
//                     -0.5f, -0.5f, 0.0f,
//                     0.5f, -0.5f, 0.0f,
//                     0.0f,  0.5f, 0.0f
//                 };

//                 GLfloat colors[] = {
//                     1.0f, 0.0f, 0.0f,
//                     0.0f, 1.0f, 0.0f,
//                     0.0f, 0.0f, 1.0f
//                 };

//                 glEnableClientState(GL_VERTEX_ARRAY);
//                 glEnableClientState(GL_COLOR_ARRAY);

//                 glVertexPointer(3, GL_FLOAT, 0, vertices);
//                 glColorPointer(3, GL_FLOAT, 0, colors);

//                 glDrawArrays(GL_TRIANGLES, 0, 3);

//                 glDisableClientState(GL_VERTEX_ARRAY);
//                 glDisableClientState(GL_COLOR_ARRAY);
//             } },

//         }
//     );

//     // auto opengl_ctx = gfx_context<gfx_api::opengl, gfx_compute::cuda, gfx_vendor::nvidia, gfx_device::dedicated>(720, 1080, "Hello Window");

//     return 0;
// }


import kernel;

int main() {
    kernel_program_start();
    return 0;
}


