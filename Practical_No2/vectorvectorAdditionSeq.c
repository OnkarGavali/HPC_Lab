#include <omp.h>
#include <stdio.h>
#include <pthread.h>
void main()
{
int N = 1000;
int A[1000];
for(int i=0;i<N;i++)A[i] = i + 1;
int B[1000];
for(int i=0;i<N;i++)B[i] = N - i;
int C[1000] = {0};
double itime, ftime, exec_time;
itime = omp_get_wtime();
for (int i = 0; i < N; i++)
{
C[i] = A[i] + B[i];
printf("Thread: %d Index: %d\n", omp_get_thread_num(),i);
}
for(int i=0;i<N;i++){
printf("%d ", C[i]);
}
ftime = omp_get_wtime();
exec_time = ftime - itime;
printf("\nTime taken is %f\n", exec_time);
printf("\n");
}
