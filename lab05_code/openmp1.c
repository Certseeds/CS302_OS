#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) 
{
	printf("Number of threads = %d\n", omp_get_num_threads());
	#pragma omp parallel
	{
	  printf("I am thread %d\n", omp_get_thread_num());
	}
}