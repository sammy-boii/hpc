#include <stdio.h>
#include <pthread.h>

void *threadOne(void *p)
{
    for (int i = 2; i < 3000; i++)
    {
        int isPrime = 1;
        for (int j = 2; j * j <= i; j++)
        {
            if (i % j == 0)
            {
                isPrime = 0; // not a prime
                break;
            }
        }

        if (isPrime)
        {
            printf("Thread one: %d\n", i);
        }
    }
}

void *threadTwo(void *p)
{

    for (int i = 3000; i < 6000; i++)
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
            printf("Thread two: %d\n", i);
        }
    }
}

void *threadThree(void *p)
{
    for (int i = 6000; i <= 10000; i++)
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
            printf("Thread three: %d\n", i);
        }
    }
}

void main()
{
    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, threadOne, NULL);
    pthread_create(&thread2, NULL, threadTwo, NULL);
    pthread_create(&thread3, NULL, threadThree, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
}