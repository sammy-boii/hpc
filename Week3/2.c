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

    int start = data->start;
    int end = data->end;
    int id = data->id;

    for (int i = start; i <= end; i++)
    {
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
            printf("Thread %d: %d\n", id, i);
        }
    }
}

void main()
{
    int n;

    printf("Enter the number of threads: ");
    scanf("%d", &n);

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

    for (int i = 0; i < n; i++)
    {
        pthread_join(threads[i], NULL);
    }
}