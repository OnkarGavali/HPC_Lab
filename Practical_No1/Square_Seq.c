//Onkar Gavali
//2019BTECS00037
//B2
//Assignment 1 q2
//Square of 1st 100 natural numbers
//Sequential code 
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
	long long int sum=0;
	int N=100;
	double itime, ftime, exec_time;
	itime = omp_get_wtime();
	for(int i=1;i<=N;i++){
		printf("Square of %d is %d \n",i,i*i);
		sum+=i*i;
	}
	ftime = omp_get_wtime();
	exec_time = ftime - itime;
	printf("Sum of 1st %d natural numbers id %lld",N,sum);
	printf("\nTime taken is %f\n", exec_time);
	return 0;
}