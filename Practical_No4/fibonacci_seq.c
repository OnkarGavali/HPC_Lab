//Onkar Gavali
//2019BTECS00037
//B2
//Assignment 4 question 1
//Fibonacci Series using Dynamic Programming 
//Sequential code 

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int fib(int n)
{

	/* Declare an array to store Fibonacci numbers. */ 
	int f[n+2]; // 1 extra to handle case, n = 0
	int i;
	/* 0th and 1st number of the series are 0 and 1*/ f[0] = 0;
	f[1] = 1;
	for (i = 2; i <= n; i++)
	{
		/* Add the previous 2 numbers in the series and store it */	 
		f[i] = f[i-1] + f[i-2];
	}
	return f[n];
}
int main ()
{
	int n = 30,result;
	double itime, ftime, exec_time;
	itime = omp_get_wtime();
	result=fib(n);	
	ftime = omp_get_wtime();
	exec_time = ftime - itime;
	printf("\nTime taken is %f\n", exec_time);
	printf("%d", result); 
	getchar();
	return 0;

}
