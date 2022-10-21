//Onkar Gavali
//2019BTECS00037
//B2
//Assignment 3 q2
// matrix multipliction
//Parallel code 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define N 2000
void add(int** a, int** b, int** c){
	#pragma omp parallel for
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}
void getMatrix(int** a, int num){
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			a[i][j] = num;
		}
	}
}
void displayMatrix(int** a){
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
}
int main(){
	int** a;
	int** b;
	int** c;
	a = malloc(sizeof(int*) * N);
	b = malloc(sizeof(int*) * N);
	c = malloc(sizeof(int*) * N);
	for(int i=0; i<N; i++){
		a[i] = malloc(sizeof(int) * N);
		b[i] = malloc(sizeof(int) * N);
		c[i] = malloc(sizeof(int) * N);
	}
	getMatrix(a, 1);
	getMatrix(b, 1);
	int thread=8;
	omp_set_num_threads(thread);
	double start;
	double end;
	start = omp_get_wtime();
	add(a, b, c);
	end = omp_get_wtime();
	printf("For 2d matrix multiplicatin \n For N=%d and thread=%d Time taken (parallel): %f\n",N,thread, end - start);
	}