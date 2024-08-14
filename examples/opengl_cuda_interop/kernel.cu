#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <curand_kernel.h>


//// CUDA kernel to set each pixel to a random color
//__global__ void kernel(uchar4* devPtr, int width, int height, int tick) {
//    int x = blockIdx.x * blockDim.x + threadIdx.x;
//    int y = blockIdx.y * blockDim.y + threadIdx.y;
//
//    if (x < width && y < height) {
//        int offset = y * width + x;
//
//        // Simple random number generator based on tick, x, and y
//        unsigned int seed = (tick + x * 1973 + y * 9277) & 0x7FFFFFFF;
//        devPtr[offset].x = (seed % 256);  // Red
//        devPtr[offset].y = ((seed >> 8) % 256);  // Green
//        devPtr[offset].z = ((seed >> 16) % 256);  // Blue
//        devPtr[offset].w = 255;  // Alpha
//    }
//}
//
//void launchKernel(uchar4* devPtr, int width, int height, int tick) {
//    dim3 blockSize(16, 16);
//    dim3 gridSize((width + blockSize.x - 1) / blockSize.x, (height + blockSize.y - 1) / blockSize.y);
//    kernel<<<gridSize, blockSize >>> (devPtr, width, height, tick);
//    cudaDeviceSynchronize();
//}

struct QuadTreeNode {
    int x, y;
    int size;
    bool isLeaf;
};

// CUDA kernel to draw the Quadtree
__global__ void drawQuadtree(uchar4* devPtr, int width, int height, QuadTreeNode* nodes, int nodeCount) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < width && y < height) {
        int offset = y * width + x;

        // Initialize the pixel as black
        devPtr[offset].x = 0;
        devPtr[offset].y = 0;
        devPtr[offset].z = 0;
        devPtr[offset].w = 255;

        // Check each node to see if the pixel lies on a quadtree boundary
        for (int i = 0; i < nodeCount; i++) {
            QuadTreeNode node = nodes[i];

            if (node.isLeaf) {
                // Draw the boundary of the node
                if (x == node.x || x == node.x + node.size - 1 || y == node.y || y == node.y + node.size - 1) {
                    devPtr[offset].x = 255;  // Red color for boundaries
                    devPtr[offset].y = 255;  // Green color for boundaries
                    devPtr[offset].z = 255;  // Blue color for boundaries
                }
            }
        }
    }
}

// CUDA kernel to generate a randomized Quadtree
__global__ void generateRandomQuadtree(QuadTreeNode* nodes, int width, int height, int maxDepth, unsigned long long seed) {
    int nodeIndex = 0;
    curandState state;
    curand_init(seed, 0, 0, &state);

    __shared__ QuadTreeNode localNodes[1024];
    __shared__ int localIndex;

    if (threadIdx.x == 0) {
        localIndex = 0;
    }
    __syncthreads();

    int x = curand(&state) % width;
    int y = curand(&state) % height;
    int size = (width < height ? width : height) / 4; // Initial size

    for (int d = 0; d < maxDepth; ++d) {
        if (localIndex < 1024) {
            localNodes[localIndex] = { x, y, size, true };
            ++localIndex;
        }
        __syncthreads();

        // Randomize size and position for the next level
        x += curand(&state) % (width - size);
        y += curand(&state) % (height - size);
        size = size / 2;
        if (size < 1) size = 1;

        __syncthreads();
    }

    // Copy results to global memory
    if (threadIdx.x == 0) {
        for (int i = 0; i < localIndex; ++i) {
            nodes[i] = localNodes[i];
        }
    }
}

void launchRandomQuadtreeKernel(uchar4* devPtr, int width, int height, int maxDepth, unsigned long long seed) {
    // Allocate memory for the quadtree nodes
    int maxNodes = (1 << (2 * maxDepth)) - 1;
    QuadTreeNode* nodes;
    cudaMalloc(&nodes, maxNodes * sizeof(QuadTreeNode));

    // Generate the random quadtree
    generateRandomQuadtree << <1, 1 >> > (nodes, width, height, maxDepth, seed);
    cudaDeviceSynchronize();

    // Draw the quadtree
    dim3 blockSize(16, 16);
    dim3 gridSize((width + blockSize.x - 1) / blockSize.x, (height + blockSize.y - 1) / blockSize.y);
    drawQuadtree << <gridSize, blockSize >> > (devPtr, width, height, nodes, maxNodes);
    cudaDeviceSynchronize();

    // Free the quadtree node memory
    cudaFree(nodes);
}
