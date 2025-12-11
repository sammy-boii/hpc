#include <stdio.h>
#include <omp.h>

int main()
{
    omp_set_num_threads(10);

#pragma omp parallel
    {
        printf("Hello world from OpenMP! Thread %d\n", omp_get_thread_num());
    }

    return 0;
}
