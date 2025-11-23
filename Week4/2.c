#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_USERS 10   // Number of users trying to print
#define NUM_PRINTERS 2 // Only 2 printers available

sem_t printer_sem; // Semaphore to control printer access

void *print_document(void *arg)
{
    int userId = *(int *)arg;

    printf("User %d is waiting to print...\n", userId);

    // Wait until a printer is available
    sem_wait(&printer_sem);

    printf("User %d is using a printer.\n", userId);
    sleep(rand() % 3 + 1); // Simulate printing time (1–3 seconds)
    printf("User %d has finished printing.\n", userId);

    // Release the printer (increment semaphore)
    sem_post(&printer_sem);

    return NULL;
}

int main()
{
    pthread_t threads[NUM_USERS];
    int userIds[NUM_USERS];

    // Initialize semaphore with value = number of printers
    sem_init(&printer_sem, 0, NUM_PRINTERS);

    srand(time(NULL));

    // Create user threads
    for (int i = 0; i < NUM_USERS; i++)
    {
        userIds[i] = i + 1;
        pthread_create(&threads[i], NULL, print_document, &userIds[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_USERS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Destroy semaphore
    sem_destroy(&printer_sem);

    printf("\nAll users have finished printing.\n");
    return 0;
}