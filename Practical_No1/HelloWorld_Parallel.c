//Onkar Gavali
//2019BTECS00037
//B2
//Assignment 1 q2
//Hello World
//parallel code 
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
	double itime, ftime, exec_time;
	itime = omp_get_wtime();
	#pragma omp parallel
	{
		int n=omp_get_thread_num();
		printf("Hello %d ",n);	
		printf("World %d\n",n);
	}
	ftime = omp_get_wtime();
	exec_time = ftime - itime;
	printf("\nTime taken is %f\n", exec_time);
	return 0;
}

/*int main(){
	double itime, ftime, exec_time;
	itime = omp_get_wtime();
	
	#pragma omp parallel for num_threads(100)
	for(int i=0;i<10000;++i){
		int n=omp_get_thread_num();
		printf("Hello %d ",n);	
		printf("World %d\n",n);
	}
	
	ftime = omp_get_wtime();
	exec_time = ftime - itime;
	printf("\nTime taken is %f\n", exec_time);
	return 0;
}*/