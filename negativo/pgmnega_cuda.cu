#include <stdio.h>
#include "pgmlib.h"

__global__ void kernel(int * device_mem, int lin, int cols, int maxval)
{
	int index = blockIdx.x * cols + threadIdx.x;

	device_mem[index] = maxval - device_mem[index];
}

int negative_cuda(PGM_t *pgm)
{
	int *device_mem;
	int size_bytes = sizeof(int) * pgm->rows * pgm->cols;

	cudaMalloc ((void **) &device_mem, size_bytes);

	cudaMemcpy ((void *) device_mem, (void *)pgm->image, size_bytes, cudaMemcpyHostToDevice);

    kernel<<<pgm->rows, pgm->cols>>>(device_mem, pgm->rows, pgm->cols, pgm->maxval);

    cudaMemcpy ((void *)pgm->image, (void *) device_mem, size_bytes, cudaMemcpyDeviceToHost);

    cudaDeviceSynchronize();

    return 0;
}