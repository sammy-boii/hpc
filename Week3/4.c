#include <stdio.h>
#include <stdlib.h>  // for malloc() and free()
#include <pthread.h> // for pthreads

typedef struct
{
    int start;
    int end;
    int id;
} ThreadData;

pthread_t *threads;                               // Array of thread identifiers
int n;                                            // Number of threads (global for easy access)
int totalPrimes = 0;                              // Shared prime counter
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // Mutex for thread-safe updates

// Thread function
void *isPrime(void *arg)
{
    ThreadData *data = (ThreadData *)arg;

    for (int i = data->start; i <= data->end; i++)
    {
        if (i < 2)
            continue;

        int prime = 1;
        for (int j = 2; j * j <= i; j++)
        {
            if (i % j == 0)
            {
                prime = 0;
                break;
            }
        }

        if (prime)
        {
            printf("Thread %d found prime: %d\n", data->id, i);

            pthread_mutex_lock(&lock);
            totalPrimes++;

            if (totalPrimes >= 5)
            {
                printf("Thread %d reached the 5th prime. Cancelling others...\n", data->id);

                for (int t = 0; t < n; t++)
                {
                    if (t != data->id)
                        pthread_cancel(threads[t]);
                }

                pthread_mutex_unlock(&lock);
                pthread_exit(NULL); // Exit after cancelling others
            }

            pthread_mutex_unlock(&lock);
        }

        pthread_testcancel(); // Make thread responsive to cancellation
    }

    pthread_exit(NULL);
}

int main()
{
    printf("Enter the number of threads: ");
    scanf("%d", &n);

    // Allocate memory for threads and thread data
    threads = malloc(n * sizeof(pthread_t));
    if (!threads)
    {
        perror("Failed to allocate memory for threads");
        return 1;
    }

    ThreadData *data = malloc(n * sizeof(ThreadData));
    if (!data)
    {
        perror("Failed to allocate memory for thread data");
        free(threads);
        return 1;
    }

    int start = 2;
    int range = (10000 + n - 1) / n; // Divide range evenly (ceil division)

    for (int i = 0; i < n; i++)
    {
        data[i].start = start;
        data[i].end = (i == n - 1) ? 10000 : start + range - 1;
        data[i].id = i;

        pthread_create(&threads[i], NULL, isPrime, &data[i]);
        start += range;
    }

    // Wait for all threads to finish (even if some were cancelled)
    for (int i = 0; i < n; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("\nTotal primes found (stopped at 5th prime): %d\n", totalPrimes);

    free(threads);
    free(data);
    pthread_mutex_destroy(&lock);

    return 0;
}
