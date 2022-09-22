#include<bits/stdc++.h>
#include <processthreadsapi.h>
#include <sysinfoapi.h>
#include<omp.h>
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
	//cpu time
	double cpu_time_begin = get_cpu_time();
	//wall time
    long long int wall_time_begin = GetTickCount();
	cout<<"Hello World\n";
	double cpu_time_end = get_cpu_time();
    long long int wall_time_end = GetTickCount();
    double cpu_time_elapsed = (cpu_time_end - cpu_time_begin);
    double wall_time_elapsed = (wall_time_end - wall_time_begin)*1e-3;
    printf("CPU Time measured: %f seconds.\n", cpu_time_elapsed);
    printf("Wall Time measured: %f seconds.\n", wall_time_elapsed);
    cout<<"======================================================================="<<endl;
}

void parallel(int n=4){

    omp_set_num_threads(n);
    //cpu time
	double cpu_time_begin = get_cpu_time();
	//wall time
    long long int wall_time_begin = GetTickCount();
	#pragma omp parallel
	{
		int id=omp_get_thread_num()
;		cout<<"Hello("<<id<<") World("<<id<<")\n";
	} 
	double cpu_time_end = get_cpu_time();
    long long int wall_time_end = GetTickCount();
    double cpu_time_elapsed = (cpu_time_end - cpu_time_begin);
    double wall_time_elapsed = (wall_time_end - wall_time_begin)*1e-3;
    printf("CPU Time measured: %f seconds.\n", cpu_time_elapsed);
    printf("Wall Time measured: %f seconds.\n", wall_time_elapsed);
    cout<<"======================================================================="<<endl;
}

int main(){
	seq();
	parallel();
	parallel(10);
	//parallel(100);	
	return 0;
}