#include<stdio.h>
#include<time.h>
#include<malloc.h>
#include<cuda.h>

#define N 32
#define n_threads 4
#define n_blocks 8

void __global__ kernelTong2Mang(int *a, int *b, int *c) {
    int index;
    index = blockIdx.x * blockDim.x + threadIdx.x;
    *(c + index) = *(a + index) + *(b + index);
}

int main(int argc, char *argv[]) {
    // HOST CODE
    int *a_cpu, *b_cpu, *c_cpu, i;
    a_cpu = (int*) malloc(N * sizeof(int));
    b_cpu = (int*) malloc(N * sizeof(int));
    c_cpu = (int*) malloc(N * sizeof(int));

    for (i = 0; i < N; i ++) {
        *(a_cpu + i) = i;
        *(b_cpu + i) = i;
    }
    
    // Khai bao bien tren GPU
    int *a_gpu, *b_gpu, *c_gpu;
    cudaMalloc((void**) &a_gpu, N * sizeof(int));
    cudaMalloc((void**) &b_gpu, N * sizeof(int));
    cudaMalloc((void**) &c_gpu, N * sizeof(int));
    
    // Copy input CPU -> GPU
    cudaMemcpy(a_gpu, a_cpu, N * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(b_gpu, b_cpu, N * sizeof(int), cudaMemcpyHostToDevice);
    
    // Define structure: thread, block
    dim3 dimBlock(n_threads);
    dim3 dimGrid(n_blocks);
    
    // Invoke kernel
    kernelTong2Mang<<<dimGrid, dimBlock>>>(a_gpu, b_gpu, c_gpu);
    
    // Copy output GPU -> CPU
    cudaMemcpy(c_cpu, c_gpu, N * sizeof(int), cudaMemcpyDeviceToHost);
    
    // Giai phong bo nho GPU
    cudaFree(a_gpu);
    cudaFree(b_gpu);
    cudaFree(c_gpu);
    
    for (i = 0; i < N; i ++) {
        printf("%d\t", *(c_cpu + i));
    }
    
    return 0;
}

