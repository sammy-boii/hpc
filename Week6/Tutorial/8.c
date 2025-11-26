#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

#define BARRIER_COUNT 100

int thread_count = 10;
int barrier_count = 0;

void Thread_work()
{
    long my_rank = omp_get_thread_num();

    sleep(my_rank);
    printf("Thread %ld waiting at barrier\n", my_rank);

#pragma omp barrier
    printf("All threads entered barrier\n");
}

int main(int argc, char *argv[])
{

#pragma omp parallel
    Thread_work();

    return 0;
}
