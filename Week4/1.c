#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    int accountNumber;
    double balance;
    pthread_mutex_t lock; // Mutex for each account
} Account;

Account accounts[10];

void *withdraw(void *p)
{
    int accountId = *(int *)p;
    double amount = 100.0; // Withdraw amount

    pthread_mutex_lock(&accounts[accountId].lock); // Lock before modifying balance
    accounts[accountId].balance -= amount;
    printf("Withdrawn %.2f from Account %d | New Balance: %.2f\n",
           amount, accountId, accounts[accountId].balance);
    pthread_mutex_unlock(&accounts[accountId].lock); // Unlock after modifying
    return NULL;
}

void *deposit(void *p)
{
    int accountId = *(int *)p;
    double amount = 100.0; // Deposit amount

    pthread_mutex_lock(&accounts[accountId].lock);
    accounts[accountId].balance += amount;
    printf("Deposited %.2f to Account %d | New Balance: %.2f\n",
           amount, accountId, accounts[accountId].balance);
    pthread_mutex_unlock(&accounts[accountId].lock);
    return NULL;
}

int main()
{
    pthread_t threads[20];
    int ids[10];

    // Initialize accounts and mutexes
    for (int i = 0; i < 10; i++)
    {
        accounts[i].accountNumber = i;
        accounts[i].balance = 1000.0; // Initial balance
        pthread_mutex_init(&accounts[i].lock, NULL);
        ids[i] = i;
    }

    // Create multiple threads to simulate concurrent transactions
    for (int i = 0; i < 10; i++)
    {
        pthread_create(&threads[i], NULL, withdraw, &ids[i]);
        pthread_create(&threads[i + 10], NULL, deposit, &ids[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < 20; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Print final balance
    printf("\nFinal Account Balances:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("Account %d balance = %.2f\n", i, accounts[i].balance);
        pthread_mutex_destroy(&accounts[i].lock); // Clean up mutex
    }

    return 0;
}
