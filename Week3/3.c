#include <stdio.h>
#include <pthread.h>

typedef struct
{
    int start;
    int end;
    int id;
} ThreadData;

void *isPrime(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    long count = 0; // number of primes found

    for (int i = data->start; i <= data->end; i++)
    {
        if (i < 2)
            continue; // skip 0 and 1

        int isPrime = 1;
        for (int j = 2; j * j <= i; j++)
        {
            if (i % j == 0)
            {
                isPrime = 0;
                break;
            }
        }

        if (isPrime)
        {
            printf("Thread %d: %d\n", data->id, i);
            count++;
        }
    }

    pthread_exit((void *)count);
}

int main()
{
    int n;
    printf("Enter the number of threads: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of threads.\n");
        return 1;
    }

    pthread_t threads[n];
    ThreadData data[n];

    int start = 2;
    int range = 10000 / n;

    for (int i = 0; i < n; i++)
    {
        data[i].start = start;
        data[i].end = (i == n - 1) ? 10000 : start + range - 1;
        data[i].id = i + 1;

        pthread_create(&threads[i], NULL, isPrime, &data[i]);
        start += range;
    }

    void *retval;

    for (int i = 0; i < n; i++)
    {
        pthread_join(threads[i], &retval);
        long count = (long)retval; // long because void pointer is also 8 bytes
        printf("Thread %d found %ld prime numbers\n", i + 1, count);
    }

    return 0;
}
