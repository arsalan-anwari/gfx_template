module;

#include <iostream>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

#include "kernel.h"

export module kernel;

void start_program() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "CUDA Randomized Quadtree", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return;
    }

    // Create an OpenGL pixel buffer object (PBO)
    GLuint pbo;
    glGenBuffers(1, &pbo);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, 800 * 600 * sizeof(uchar4), nullptr, GL_DYNAMIC_COPY);

    // Register the PBO with CUDA
    cudaGraphicsResource* cudaPboResource;
    cudaGraphicsGLRegisterBuffer(&cudaPboResource, pbo, cudaGraphicsMapFlagsWriteDiscard);

    int maxDepth = 5;  // Set the depth of the Quadtree
    unsigned long long frameSeed = 0;

    while (!glfwWindowShouldClose(window)) {
        // Map the PBO to CUDA
        uchar4* devPtr;
        size_t size;
        cudaGraphicsMapResources(1, &cudaPboResource, 0);
        cudaGraphicsResourceGetMappedPointer((void**)&devPtr, &size, cudaPboResource);

        // Launch the randomized quadtree kernel
        frameSeed++;  // Change the seed for each frame
        launchRandomQuadtreeKernel(devPtr, 800, 600, maxDepth, frameSeed);

        // Unmap the PBO
        cudaGraphicsUnmapResources(1, &cudaPboResource, 0);

        // Render the PBO as a texture
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawPixels(800, 600, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // Cleanup
    cudaGraphicsUnregisterResource(cudaPboResource);
    glDeleteBuffers(1, &pbo);
    glfwDestroyWindow(window);
    glfwTerminate();
}

export void kernel_program_start() {
    std::cout << "Starting kernel program" << std::endl;
    start_program();
}