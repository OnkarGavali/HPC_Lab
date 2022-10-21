//Onkar Gavali
//2019BTECS00037
//B2
//Assignment 3 q1
// C Program to find the minimum scalar product of two vectors
//(dot product)
//Parallel code 

#include <stdio.h>
#include <time.h>
#include<omp.h>
#define n 100000
// below 100000 seq is faster
//even odd sort
int sort(int arr[])
{
	int i, j;
	for (i = 0; i < n; i++){
		int turn = i % 2;
		#pragma omp parallel for
		for (j = turn; j < n - 1; j+=2)
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
	}
}
int sort_des(int arr[])
{
	int i, j;
	for (i = 0; i < n; ++i)
	{
		int turn = i % 2;
		#pragma omp parallel for
		for (j = turn; j < n - 1; j += 2)
		{
			if (arr[j] < arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
int main()
{
	int arr1[n], arr2[n];
	int i;
	for (i = 0; i < n; i++)
	{
		arr1[i] = n - i;
	}
	for (i = 0; i < n; i++)
	{
		arr2[i] = i;
	}
	clock_t t;
	t = clock();
	/*
	#pragma omp parellel for 
	for(int i=0;i<2;++i){
		if(i==0){
			sort(arr1);
		}else{
			sort_des(arr2);
		}
	}	
	*/
	sort(arr1);
	sort_des(arr2);
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("Time taken (seq): %f\n", time_taken);
	long long int sum = 0;
	for (i = 0; i < n; i++)
	{
		sum = sum + (arr1[i] * arr2[i]);
	}
	printf("%lld\n", sum);
	return 0;
}