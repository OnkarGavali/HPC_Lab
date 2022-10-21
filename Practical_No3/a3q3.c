//Onkar Gavali
//2019BTECS00037
//B2
//Assignment 3 q3
// Demostrate use of nowait clause
//parallel code

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 10
void noWaitFun(){
	printf("This is no wait clause\n");
}
void forLoop(int i){
	printf("In the for loop: %d\n", i);
}
int main(){
	int* a = malloc(sizeof(int) * N);
	for(int i=0; i<N; i++){
		a[i] = 1;
	}
	#pragma omp parallel
	{
		#pragma omp for nowait
		for(int i=0; i<N; i++){
			forLoop(i);
		}
		noWaitFun();
	}
}