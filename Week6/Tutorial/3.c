#include <stdio.h>
#include <omp.h>
void threadOne()
{
    int i, c;
    int nstart = 1, nfinish = 10000;

#pragma omp parallel for
    for (i = nstart; i <= nfinish; i++)
    {
        for (c = 2; c <= i - 1; c++)
        {
            if (i % c == 0)
                break;
        }
        if (c == i)
            printf("threadOne : %d\n", i);
    }
}

void threadTwo()
{
    int i, c;
    int nstart = 10001, nfinish = 20000;

#pragma omp parallel for
    for (i = nstart; i <= nfinish; i++)
    {
        for (c = 2; c <= i - 1; c++)
        {
            if (i % c == 0)
                break;
        }
        if (c == i)
            printf("threadTwo : %d\n", i);
    }
}
int main()
{
    printf("Prime numbers between 1 and 20000 are:\n");
#pragma omp parallel sections
    {
#pragma omp section
        {
            threadOne();
        }

#pragma omp section
        {
            threadTwo();
        }
    }

    return 0;
}
