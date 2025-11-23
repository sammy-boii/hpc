#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

char *messages[3] = {NULL, NULL, NULL};
volatile int turn = 0;

void *messenger(void *p)
{
    long tid = (long)p;
    char tmpbuf[100];

    for (int i = 0; i < 10; i++)
    {
        while (turn != tid)
            ;

        long dest = (tid + 1) % 3;
        sprintf(tmpbuf, "Hello from Thread %ld!", tid);
        messages[dest] = strdup(tmpbuf);
        printf("Thread %ld sent the message to Thread %ld\n", tid, dest);

        printf("Thread %ld received the message '%s'\n", tid, messages[tid]);
        free(messages[tid]);
        messages[tid] = NULL;

        turn = dest;
    }
    return NULL;
}

int main()
{
    pthread_t thrID[3];

    for (long i = 0; i < 3; i++)
        pthread_create(&thrID[i], NULL, messenger, (void *)i);

    for (int i = 0; i < 3; i++)
        pthread_join(thrID[i], NULL);

    return 0;
}
