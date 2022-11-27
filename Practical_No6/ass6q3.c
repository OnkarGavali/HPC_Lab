
#include <mpi.h>
#include <stdio.h>

#define localSize 1000

int local[1000]; // to store the subarray data comming from process 0;

int init(int *arr,int n){
    for(int i=0;i<n;++i){
        arr[i]=1;
    }
}

int main(int argc, char **argv)
{
    int rank;
    int num;

    int n = 10;
    int arr[10] ;
    init(arr,n);
    int per_process, elements_received, partial_sum=0,sum=0;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &num);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Status status;

    
    
        int index, i;

        per_process = n / num;
        if(n%num!=0){
            per_process++;
        }

        int start = rank*per_process;
        int end=start+per_process;

        for(int i=start;i<end;++i){
            if(i<n){
                sum+=arr[i];
            }
        }
        if(rank!=0){
            MPI_Send(&sum,1,MPI_INT,0,0,MPI_COMM_WORLD);
        }else{
            for(int i=1;i<num;++i){
                MPI_Recv(&partial_sum,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                sum+=partial_sum;
            }
            printf("%d",sum);
        }
    MPI_Finalize();
    return 0;
}