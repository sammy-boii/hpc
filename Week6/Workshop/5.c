#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

char *messages[3] = {NULL, NULL, NULL};

int main()
{
#pragma omp parallel num_threads(3) shared(messages)
    {
        int tid = omp_get_thread_num();
        char tmpbuf[100];

        for (int i = 0; i < 10; i++)
        {

            int dest = (tid + 1) % 3;
            sprintf(tmpbuf, "Hello from Thread %d!", tid);

#pragma omp critical
            {
                messages[dest] = strdup(tmpbuf);
                printf("Thread %d sent the message to Thread %d\n", tid, dest);
            }

#pragma omp barrier

#pragma omp critical
            {
                printf("Thread %d received the message '%s'\n",
                       tid, messages[tid]);
                free(messages[tid]);
                messages[tid] = NULL;
            }

#pragma omp barrier
        }
    }

    return 0;
}
