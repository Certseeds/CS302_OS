#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main (int argc, char *argv[]) 
{
	int a[80],b[80],c[80];
	for(int i=0;i<80;++i)
	{
		a[i] = i;
		b[i] = 2*i;
	}

	#pragma omp parallel for
	for (int i = 0; i < 80; ++i)
	{
		c[i] = a[i] + b[i];
		printf("i=%d, c[i]=%d\n", i, c[i]);
	}
}