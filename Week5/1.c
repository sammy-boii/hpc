#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int m, n; // rows and columns
int thread_count;

// y = A*x

double **A;
double *x;
double *y;

void *multiply(void *rank)
{
    long my_rank = (long)rank;
    int row_per_thread = m / thread_count;
    int start = my_rank * row_per_thread;
    int end = (my_rank == thread_count - 1) ? m - 1 : start + row_per_thread - 1;

    for (int i = start; i <= end; i++)
    {
        y[i] = 0.0;
        for (int j = 0; j < n; j++)
            y[i] += A[i][j] * x[j];
    }
    return NULL;
}

int main()
{
    long thread;
    pthread_t *thread_handles;

    printf("Enter number of rows (m): ");
    scanf("%d", &m);
    printf("Enter number of columns (n): ");
    scanf("%d", &n);
    printf("Enter number of threads: ");
    scanf("%d", &thread_count);

    A = malloc(m * sizeof(double *));
    for (int i = 0; i < m; i++)
        A[i] = malloc(n * sizeof(double));

    x = malloc(n * sizeof(double));
    y = malloc(m * sizeof(double));
    thread_handles = malloc(thread_count * sizeof(pthread_t));

    printf("\nEnter matrix A (%d x %d):\n", m, n);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);

    printf("\nEnter vector x (%d elements):\n", n);
    for (int j = 0; j < n; j++)
        scanf("%lf", &x[j]);

    for (thread = 0; thread < thread_count; thread++)
        pthread_create(&thread_handles[thread], NULL, multiply, (void *)thread);

    for (thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread], NULL);

    printf("\nResult vector y = A * x:\n");
    for (int i = 0; i < m; i++)
        printf("%.2f ", y[i]);
    printf("\n");

    return 0;
}
