//Onkar Gavali
//2019BTECS00037
//B2
//Assignment 1 q2
//Hello World
//sequential code 
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
	int n=omp_get_thread_num();
	double itime, ftime, exec_time;
	itime = omp_get_wtime();
	printf("Hello %d ",n);	
	printf("World %d\n",n);
	ftime = omp_get_wtime();
	exec_time = ftime - itime;
	printf("\nTime taken is %f\n", exec_time);
	return 0;
}


/*int main(){
	int n=omp_get_thread_num();
	printf("Hello World written 10 times using pure for loop\n");
	double itime, ftime, exec_time;
	itime = omp_get_wtime();
	for(int i=0;i<10000;++i){
		printf("Hello %d ",n);	
		printf("World %d\n",n);
	}
	ftime = omp_get_wtime();
	exec_time = ftime - itime;
	printf("\nTime taken is %f\n", exec_time);
	return 0;
}*/