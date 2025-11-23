#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

char *messages[3] = {NULL, NULL, NULL};
sem_t sem[3];

void *messenger(void *p)
{
    long tid = (long)p;
    char tmpbuf[100];

    for (int i = 0; i < 10; i++)
    {
        sem_wait(&sem[tid]);

        long dest = (tid + 1) % 3;
        sprintf(tmpbuf, "Hello from Thread %ld!", tid);
        messages[dest] = strdup(tmpbuf);
        printf("Thread %ld sent the message to Thread %ld\n", tid, dest);

        printf("Thread %ld received the message '%s'\n", tid, messages[tid]);
        free(messages[tid]);
        messages[tid] = NULL;

        sem_post(&sem[dest]);
    }
    return NULL;
}

int main()
{
    pthread_t thrID[3];
    for (int i = 0; i < 3; i++)
        sem_init(&sem[i], 0, 0);

    sem_post(&sem[0]);

    for (long i = 0; i < 3; i++)
        pthread_create(&thrID[i], NULL, messenger, (void *)i);

    for (int i = 0; i < 3; i++)
        pthread_join(thrID[i], NULL);

    for (int i = 0; i < 3; i++)
        sem_destroy(&sem[i]);

    return 0;
}
