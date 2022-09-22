#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int fib(int n) {
	int i, j;
	if (n<2)
		return n;
	else {
		#pragma omp task shared(i)
		i=fib(n-1);
		#pragma omp task shared(j)
		j=fib(n-2);
		#pragma omp taskwait
		return i+j;
	}
}
int main(int argc, char **argv){
	int result;
	int n[5]={2,4,6,10,15};
	for(int i=0;i<5;++i){
		#pragma omp parallel
		{
		#pragma omp single
		result = fib(n[i]);
		}
		printf("for n=%d Result is %d\n",n[i], result);
	}
	
	
}