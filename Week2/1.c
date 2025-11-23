#include <stdio.h>
#include <pthread.h>

void *threadOne(void *p)
{
    for (int i = 0; i < 1000; i++)
    {
        printf("Thread One: %d\n", i);
    }
}

void *threadTwo(void *p)
{
    for (int i = 0; i < 1000; i++)
    {
        printf("Thread Two: %d\n", i);
    }
}

void main()
{
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, threadOne, NULL);
    pthread_create(&thread2, NULL, threadTwo, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Main Thread Finished\n");
}