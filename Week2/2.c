#include <stdio.h>
#include <pthread.h>

void *threadOne(void *p)
{
    int i, c;
    int nstart = 0;
    int nfinish = 100000;
    for (i = nstart; i <= nfinish; i++)
    {
        for (c = 2; c <= i - 1; c++)
        {
            if (i % c == 0)
            {
                break;
            }
        }
        if (c == i)
        {
            printf("Thread One: %d is a prime number\n", i);
        }
    }
}

void *threadTwo(void *p)
{
    int i, c;
    int nstart = 100001;
    int nfinish = 200000;
    for (i = nstart; i <= nfinish; i++)
    {

        for (c = 2; c <= i - 1; c++)
        {
            if (i % c == 0)
            {
                break;
            }
        }
        if (c == i)
        {
            printf("Thread Two: %d is a prime number\n", i);
        }
    }
}

int main()
{
    pthread_t thread1;

    pthread_create(&thread1, NULL, threadOne, NULL);
    pthread_join(thread1, NULL);

    printf("Main Thread Finished\n");
    return 0;
}