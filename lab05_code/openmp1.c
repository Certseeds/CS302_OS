/*
 * @Github: https://github.com/Certseeds
 * @Organization: SUSTech
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-03-18 16:35:19
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

//gcc openmp1.c -o openmp1 -fopenmp
int main(int argc, char *argv[]) {
    printf("Number of threads = %d\n", omp_get_num_threads());
#pragma omp parallel
    {
        printf("I am thread %d\n", omp_get_thread_num());
    }
}