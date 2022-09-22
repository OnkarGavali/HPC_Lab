// C Program to find the minimum scalar product of two vectors
//(dot product)
#include <stdio.h>
#include <time.h>
#define n 100000
int sort(int arr[])
{
int i, j;
for (i = 0; i < n - 1; i++)
for (j = 0; j < n - i - 1; j++)
if (arr[j] > arr[j + 1])
{
int temp = arr[j];
arr[j] = arr[j + 1];
arr[j + 1] = temp;
}
}
int sort_des(int arr[])
{
int i, j;
for (i = 0; i < n; ++i)
{
for (j = i + 1; j < n; ++j)
{
if (arr[i] < arr[j])
{
int a = arr[i];
arr[i] = arr[j];
arr[j] = a;
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
//scanf("%d", &arr1[i]);
arr1[i] = n - i;
}
for (i = 0; i < n; i++)
{
//scanf("%d", &arr2[i]);
arr2[i] = i;
}
clock_t t;
t = clock();
sort(arr1);
sort_des(arr2);
t = clock() - t;
double time_taken = ((double)t)/CLOCKS_PER_SEC;
printf("Time taken (seq): %f\n", time_taken);
int sum = 0;
for (i = 0; i < n; i++)
{
sum = sum + (arr1[i] * arr2[i]);
}
printf("%d\n", sum);
return 0;
}
