#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int fib(int n) {
	int i, j;
	if (n<2)
		return n;
	else {
		#pragma omp task lastprivate(i)
		{
		i=fib(n-1);
			
		}
		#pragma omp task shared(j)
		j=fib(n-2);
		#pragma omp taskwait
		return i+j;
	}
}
int main(){
	int result;
	int n[5]={2,4,6,10,20};
	double itime, ftime, exec_time;
	itime = omp_get_wtime();
	for(int i=0;i<5;++i){
		#pragma omp parallel
		{
			#pragma omp single
			result = fib(n[i]);
		}
		printf("for n=%d Result is %d\n",n[i], result);	
	}
	ftime = omp_get_wtime();
	exec_time = ftime - itime;
	printf("\nTime taken is %f\n", exec_time);
	
	//single number
	/*
	int num=20;
	itime = omp_get_wtime();
	#pragma omp parallel
	{
		#pragma omp single
		result = fib(num);
	}
	ftime = omp_get_wtime();
	exec_time = ftime - itime;
	printf("\nTime taken is %f\n", exec_time);
	printf("for n=%d Result is %d\n",num, result);
	*/
}