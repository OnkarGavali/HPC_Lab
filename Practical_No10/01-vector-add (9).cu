#include <bits/stdc++.h>
 
using std::accumulate;
using std::generate;
using std::cout;
using std::vector;
#define SHMEM_SIZE 1024

void init(vector<int>& h_v){
    for(int i=0;i<h_v.size();++i){
        h_v[i]=rand()%10;
    }
}

 __global__ void scan(int *g_odata, int *g_idata, int *tmp, int n ) 
 {   
    extern __shared__ int temp[1024];
    int thid = threadIdx.x;
    int dataid = blockDim.x*blockIdx.x+threadIdx.x;
    temp[thid] =g_idata[dataid];  
    __syncthreads();   
    for (int offset = 1; offset < n && offset<blockDim.x; offset *= 2)   
    {     
        if (thid >= offset)       
            temp[thid] = temp[thid - offset]+ temp[thid];     
        __syncthreads();   
    }   
    g_odata[dataid] = temp[thid];
    if(thid==blockDim.x-1){tmp[blockIdx.x]=temp[thid];}
} 
 
 /*__global__ void block_scan(int *g_odata,int *tmp, int n) 
 {   
    int dataid = blockDim.x*blockIdx.x+threadIdx.x;
    if(dataid>=n) return;
    tmp[dataid] =g_odata[dataid];  
    __syncthreads();
    for (int offset = 1; offset < gridDim.x ; offset *= 2)   
    {     
        if (dataid >= offset*blockDim.x)  
        {
            if((blockDim.x*blockIdx.x-((offset-1)*blockDim.x)-1)>=0){
                //all in all elements
                tmp[dataid] += tmp[blockDim.x*blockIdx.x-((offset-1)*blockDim.x)-1]; 
            }
             
        }
        __syncthreads();   
    }   
    g_odata[dataid] = tmp[dataid];
}*/


 __global__ void block_sum(int *d_v_r,int *tmp, int n) 
 {   
    int dataid = blockDim.x*blockIdx.x+threadIdx.x;
    if(blockIdx.x>0 && dataid<n)
       d_v_r[dataid]+=tmp[blockIdx.x-1];
}
 
int main() {
    // Vector size
    int N = 1 << 12;
    //N = 50;
    size_t bytes = N * sizeof(int);
 
    // Host data
    vector<int> h_v(N);
    vector<int> h_v_r(N);
    
 
    // Initialize the input data
  
    init(h_v);
     /*for(int i=0;i<N;++i){
        cout<<h_v[i]<<" ";
    }
    cout<<"\n";*/
    // Allocate device memory
    int *d_v, *d_v_r,*tmp,*tmp2;
    cudaMallocManaged(&d_v, bytes);
    cudaMallocManaged(&d_v_r, bytes);
    
    
    // Copy to device
    cudaMemcpy(d_v, h_v.data(), bytes, cudaMemcpyHostToDevice);
    
    /*for(int i=0;i<N;++i){
        cout<<d_v[i]<<" ";
    }*/
    // TB Size
    cout<<"\n";
    const int TB_SIZE = 32;
 
    // Grid Size (No padding)
    int GRID_SIZE = (N+TB_SIZE-1)/TB_SIZE;
     cudaMallocManaged(&tmp, GRID_SIZE*sizeof(int));
      cudaMallocManaged(&tmp2, GRID_SIZE*sizeof(int));
    // Call kernels
      
    scan<<<GRID_SIZE,TB_SIZE>>>(d_v_r,d_v,tmp,N);
    scan<<<1,GRID_SIZE>>>(tmp2,tmp,tmp,GRID_SIZE);
    //block_scan<<<GRID_SIZE,TB_SIZE>>>(d_v_r,tmp,N);
    block_sum<<<GRID_SIZE,TB_SIZE>>>(d_v_r,tmp2,N);
   
 
    // Copy to host;
    cudaMemcpy(h_v_r.data(), d_v_r, bytes, cudaMemcpyDeviceToHost);
    /* for(int i=0;i<N;++i){
        cout<<h_v_r[i]<<" ";
    }*/
    int t=0;
    for(int i=0;i<N;i++){
        t+=h_v[i];
        if(t!=h_v_r[i]){
            cout<<"Failed";
            cout<<i;
            break;
        }
    }
    cout << "COMPLETED SUCCESSFULLY\n";
 
    return 0;
}