# GFX Template

Generic CMake template for C++23 with different GFX technologies like OpenGL, Vulkan, DX11, with compute libraries like CUDA, OpenCL, HIP to get you started with running Graphics application in comnination with GPGPU compute using a generic interface for your own projects. This way you can focus on the core logic and dont have to worry about trivial things like the context management, device selection, data sharing between contexts, input handling, etc. 

Tweak the `VCPKG_FEATURE_FLAGS` in `CmakePresets.json` to select which combination of gfx tools and compute tools you want. C++ module support was initially planned, but intellisense for IDEs like visual studio code using cmake are not working as of date (10-08-2024).

Tweak the `VCPKG_TARGET_TRIPLET` in `CmakePresets.json` to select your host os. Beware only static linking is supported, due to use of custom repositories and projects wich dont have dynamic libraries available!

Supported right now:
- Multi device OpenGL context with shared CUDA textures

In the future i hope to implement more combinations of GFX and compute tools. 

