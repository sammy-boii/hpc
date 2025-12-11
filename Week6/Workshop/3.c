#include <stdio.h>
#include <omp.h>

void main()
{
    int i, c;
    printf("Prime numbers between 1 and 1000 are:\n");
#pragma omp parallel num_threads(5) private(i, c)
    {
#pragma omp for
        for (i = 2; i <= 1000; i++)
        {
            for (c = 2; c <= i - 1; c++)
            {
                if (i % c == 0)
                    break;
            }
            if (c == i)
            {
                int tid = omp_get_thread_num();
                printf("Thread %d: %d\n", tid, i);
            }
        }
    }
}
