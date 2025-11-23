#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

char *messages[3] = {NULL, NULL, NULL};
pthread_mutex_t mutex[3];

void *messenger(void *p)
{
    long tid = (long)p;
    char tmpbuf[100];

    for (int i = 0; i < 10; i++)
    {
        long dest = (tid + 1) % 3;

        pthread_mutex_lock(&mutex[dest]);
        sprintf(tmpbuf, "Hello from Thread %ld!", tid);
        messages[dest] = strdup(tmpbuf);
        printf("Thread %ld sent the message to Thread %ld\n", tid, dest);
        pthread_mutex_unlock(&mutex[dest]);

        pthread_mutex_lock(&mutex[tid]);
        while (messages[tid] == NULL)
            pthread_mutex_unlock(&mutex[tid]), usleep(1000), pthread_mutex_lock(&mutex[tid]);
        printf("Thread %ld received the message '%s'\n", tid, messages[tid]);
        free(messages[tid]);
        messages[tid] = NULL;
        pthread_mutex_unlock(&mutex[tid]);
    }
    return NULL;
}

int main()
{
    pthread_t thrID[3];
    for (int i = 0; i < 3; i++)
        pthread_mutex_init(&mutex[i], NULL);

    for (long i = 0; i < 3; i++)
        pthread_create(&thrID[i], NULL, messenger, (void *)i);

    for (int i = 0; i < 3; i++)
        pthread_join(thrID[i], NULL);

    for (int i = 0; i < 3; i++)
        pthread_mutex_destroy(&mutex[i]);

    return 0;
}
