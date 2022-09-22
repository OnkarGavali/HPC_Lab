#include<iostream>
#include<omp.h>
#include <processthreadsapi.h>
#include <sysinfoapi.h>
using namespace std;
double get_cpu_time(){
    FILETIME a,b,c,d;
    if (GetProcessTimes(GetCurrentProcess(),&a,&b,&c,&d) != 0){
        //  Returns total user time.
        //  Can be tweaked to include kernel times as well.
        return
            (double)(d.dwLowDateTime |
            ((unsigned long long)d.dwHighDateTime << 32)) * 0.0000001;
    }else{
        //  Handle error
        return 0;
    }
}

void seq(){
	long long int sum=0;
	//cpu time
	double cpu_time_begin = get_cpu_time();
	//wall time
    long long int wall_time_begin = GetTickCount();
	for(int i=1;i<=300;i++){
		//cout<<" Number : "<<i<<" Square : "<<i*i<<" "<<endl;
		sum+=i*i;
	}
	double cpu_time_end = get_cpu_time();
    long long int wall_time_end = GetTickCount();
	cout<<"sum of 1st 100 numbers "<<sum<<endl;
    double cpu_time_elapsed = (cpu_time_end - cpu_time_begin);
    double wall_time_elapsed = (wall_time_end - wall_time_begin)*1e-3;
    printf("CPU Time measured: %f seconds.\n", cpu_time_elapsed);
    printf("Wall Time measured: %f seconds.\n", wall_time_elapsed);
    cout<<"======================================================================="<<endl;
}

void parallel1(){
	long long int sum=0;
	
	//cpu time
	double cpu_time_begin = get_cpu_time();
	//wall time
    long long int wall_time_begin = GetTickCount();
	#pragma omp parallel
	{	
		int n=omp_get_num_threads() ;
		for(int i=omp_get_thread_num()+1;i<=300;i+=n){
			//cout<<"thread No. "<<omp_get_thread_num()<<" Number : "<<i<<" Square : "<<i*i<<" "<<endl;
			sum+=i*i;
			
		}
	}
	double cpu_time_end = get_cpu_time();
    long long int wall_time_end = GetTickCount();
	cout<<"sum of 1st 100 numbers "<<sum<<endl;
    double cpu_time_elapsed = (cpu_time_end - cpu_time_begin);
    double wall_time_elapsed = (wall_time_end - wall_time_begin)*1e-3;
    printf("CPU Time measured: %f seconds.\n", cpu_time_elapsed);
    printf("Wall Time measured: %f seconds.\n", wall_time_elapsed);
    cout<<"======================================================================="<<endl;
}

void parallel2(){
	long long int sum=0;
	//cpu time
	double cpu_time_begin = get_cpu_time();
	//wall time
    long long int wall_time_begin = GetTickCount();
	#pragma omp parallel for
	for(int i=1;i<=300;i++){
		//cout<<"thread No. "<<omp_get_thread_num()<<" Number : "<<i<<" Square : "<<i*i<<" "<<endl;
		sum+=i*i;
	}
	double cpu_time_end = get_cpu_time();
    long long int wall_time_end = GetTickCount();
	cout<<"sum of 1st 100 numbers "<<sum<<endl;
    double cpu_time_elapsed = (cpu_time_end - cpu_time_begin);
    double wall_time_elapsed = (wall_time_end - wall_time_begin)*1e-3;
    printf("CPU Time measured: %f seconds.\n", cpu_time_elapsed);
    printf("Wall Time measured: %f seconds.\n", wall_time_elapsed);
    cout<<"======================================================================="<<endl;
}

int main(){
	seq();
	parallel1();
	parallel2();
	return 0;
}