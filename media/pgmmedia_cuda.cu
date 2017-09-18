#include <stdio.h>
#include "pgmlib.h"

__global__ void kernel(int * d_in, int * d_out, int lin, int cols, int maxval)
{
	int index = blockIdx.x * cols + threadIdx.x;
	int sum = 0;

	//interior da matriz
	if(blockIdx.x > 1 && threadIdx.x > 1 && blockIdx.x < lin-2 && threadIdx.x < cols-2)
	{
		sum += d_in[(blockIdx.x-1) * cols + threadIdx.x-1];
		sum += d_in[(blockIdx.x-1) * cols + threadIdx.x  ];
		sum += d_in[(blockIdx.x-1) * cols + threadIdx.x+1];
		sum += d_in[ blockIdx.x    * cols + threadIdx.x-1];
		sum += d_in[ blockIdx.x    * cols + threadIdx.x  ];
		sum += d_in[ blockIdx.x    * cols + threadIdx.x+1];
		sum += d_in[(blockIdx.x+1) * cols + threadIdx.x-1];
		sum += d_in[(blockIdx.x+1) * cols + threadIdx.x  ];
		sum += d_in[(blockIdx.x+1) * cols + threadIdx.x+1];

		d_out[index] = sum / 9;
	}
}

int media_cuda(PGM_t *pgm, PGM_t *pgm_result)
{
	int *d_in, *d_out;
	int size_bytes = sizeof(int) * pgm->rows * pgm->cols;

	cudaMalloc ((void **) &d_in,  size_bytes);
	cudaMalloc ((void **) &d_out, size_bytes);

	cudaMemset(d_out, 0, size_bytes);

	cudaMemcpy ((void *) d_in, (void *) pgm->image, size_bytes, cudaMemcpyHostToDevice);

    kernel<<<pgm->rows, pgm->cols>>>(d_in, d_out, pgm->rows, pgm->cols, pgm->maxval);

    cudaMemcpy ((void *)pgm_result->image, (void *) d_out, size_bytes, cudaMemcpyDeviceToHost);

    cudaDeviceSynchronize();

    return 0;
}