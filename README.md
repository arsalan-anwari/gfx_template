# GFX Template

Generic vscode template using CMake and C++23 with different GFX technologies like OpenGL, Vulkan, DX11, QT to get you started with running Graphics libraries using a generic interface for your own projects. This way you can focus on the core grahics library of choice and dont have to worry about trivial things like the GFX context, input handling, etc. 

It used C++ modules by default and allows you to configure which technologies to use by tweaking the `VCPKG_FEATURE_FLAGS` or by chosing a different CMake Target.

Right now only OpenGL through GlEW and using a window context through GLFW is supported, but in the future you can chose to mix things like QT for the UI and context, Vulkan for the graphics and OpenCL for the compute. 

