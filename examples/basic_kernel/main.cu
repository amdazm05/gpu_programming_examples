#include <iostream>
#include <math.h>
#include <cuda_profiler_api.h>

//To profile this use : sudo nvprof --unified-memory-profiling off ./basic_kernel_example

#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort=true)
{
   if (code != cudaSuccess) 
   {
      fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
      if (abort) exit(code);
   }
}

__global__
void initialise(int n, float *x, float *y)
{
  int index = blockIdx.x * blockDim.x + threadIdx.x;
  int stride = blockDim.x * gridDim.x;
  for (int i = index; i < n; i += stride)
  {
    y[i] = 2.0f;
	x[i] = 1.0f;
  }
}

__global__
void add(int n, float *x, float *y)
{
  int index = blockIdx.x * blockDim.x + threadIdx.x;
  int stride = blockDim.x * gridDim.x;
  for (int i = index; i < n; i += stride)
    y[i] = x[i] + y[i];
}


int main(int argc, char **argv)
{
	
	int N = 1<<20;
	int blockSize = 512;
	int numBlocks = (N + blockSize - 1) / blockSize;

	float * x;
	float * y;
	
	gpuErrchk(cudaMallocManaged(&x,N*sizeof(float)));
	gpuErrchk(cudaMallocManaged(&y,N*sizeof(float)));

	std::cout<<"POST ALLOCATION"<<std::endl;
	
	initialise<<<numBlocks,blockSize>>>(N,x,y);
	add<<<numBlocks, blockSize>>>(N, x, y);


	cudaFree(x);
	cudaFree(y);

	cudaDeviceReset();

	return EXIT_SUCCESS;
}

//some notes on profiling
//sudo nvprof --unified-memory-profiling off ./${executable} should make the profiling work 
//more here https://forums.developer.nvidia.com/t/nvprof-error-code-139-but-memcheck-ok/50329

