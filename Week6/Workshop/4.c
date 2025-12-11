#include <stdio.h>
#include <omp.h>

int main()
{
    int i, c;
    int total_primes = 0;
    printf("Prime numbers between 1 and 1000 are:\n");
#pragma omp parallel num_threads(1) private(i, c) reduction(+ : total_primes)
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
                total_primes++;
                int tid = omp_get_thread_num();
                printf("Thread %d: %d\n", tid, i);
            }
        }
    }
    printf("Total primes = %d\n", total_primes);
    return 0;
}
