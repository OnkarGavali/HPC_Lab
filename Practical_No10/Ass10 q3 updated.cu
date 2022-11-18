#include <bits/stdc++.h>
 
using std::accumulate;
using std::generate;
using std::cout;
using std::vector;
#define SHMEM_SIZE 16

void init(vector<int>& h_v){
    for(int i=0;i<h_v.size();++i){
        h_v[i]=rand()%10;
    }
}

__global__ void prefixSum(int *v, int *v_r) {
    // Allocate shared memory
    __shared__ int partial_sum[SHMEM_SIZE];
 
    // Calculate thread ID
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
 
    // Load elements into shared memory
    partial_sum[threadIdx.x] = v[tid];
    __syncthreads();
 
    // Iterate of log base 2 the block dimension
    for (int s = 1; s < blockDim.x; s *= 2) {
        // Reduce the threads performing work by half previous the previous
        // iteration each cycle
        if (threadIdx.x % (2 * s) == 0) {
            partial_sum[threadIdx.x] += partial_sum[threadIdx.x + s];
        }
        __syncthreads();
    }
 
    // Let the thread 0 for this block write it's result to main memory
    // Result is inexed by this block
    if (threadIdx.x == 0) {
        v_r[blockIdx.x] = partial_sum[0];
    }
}

 __global__ void scan(int *g_odata, int *g_idata, int n) 
 {   
    extern __shared__ int temp[16]; // allocated on invocation 
    
    int thid = threadIdx.x;   
    
    
    
    temp[thid] =g_idata[thid];  
    
    __syncthreads();   
    //cout<<thid<<" "<<temp[pout*n + thid]<<"\n";
    for (int offset = 1; offset < n; offset *= 2)   
    {     
        
        if (thid >= offset)       
            temp[thid] = temp[thid - offset]+ temp[thid];     
            
        __syncthreads();   
    }   
    g_odata[thid] = temp[thid]; 
    // write output 
} 
 
int main() {
    // Vector size
    int N = 1 << 16;
    N = 16;
    size_t bytes = N * sizeof(int);
 
    // Host data
    vector<int> h_v(N);
    vector<int> h_v_r(N+1);
 
  // Initialize the input data
  
      init(h_v);
     for(int i=0;i<N;++i){
        cout<<h_v[i]<<" ";
    }
    cout<<"\n";
    // Allocate device memory
    int *d_v, *d_v_r;
    cudaMallocManaged(&d_v, bytes);
    cudaMallocManaged(&d_v_r, bytes);
    
    // Copy to device
    cudaMemcpy(d_v, h_v.data(), bytes, cudaMemcpyHostToDevice);
    
    for(int i=0;i<N;++i){
        cout<<d_v[i]<<" ";
    }
    // TB Size
    cout<<"\n";
    const int TB_SIZE = 16;
 
    // Grid Size (No padding)
    int GRID_SIZE = 1;
 
    // Call kernels
    //prefixSum<<<1, N>>>(d_v, d_v_r);
    scan<<<1,N>>>(d_v_r,d_v,N);
    //prefixSum<<<1, TB_SIZE>>> (d_v_r, d_v_r);
 
    // Copy to host;
    cudaMemcpy(h_v_r.data(), d_v_r, bytes, cudaMemcpyDeviceToHost);
 
    // Print the result
    //assert(h_v_r[0] == std::accumulate(h_v.begin(), h_v.end(), 0));
     
     
      for(int i=0;i<N;++i){
        cout<<h_v_r[i]<<" ";
    }
     
    cout << "COMPLETED SUCCESSFULLY\n";
 
    return 0;
}
