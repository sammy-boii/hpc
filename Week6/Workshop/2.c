#include <stdio.h>
#include <omp.h>

int main()
{
    int i, c;
    printf("Prime numbers between 1 and 1000 are:\n");

#pragma omp parallel for private(c)
    for (i = 2; i <= 1000; i++)
    {
        for (c = 2; c <= i - 1; c++)
        {
            if (i % c == 0)
                break;
        }
        if (c == i)
        {
            printf("%d\n", i);
        }
    }
    return 0;
}
