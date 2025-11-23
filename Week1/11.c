// prime check using function

#include <stdio.h>

int isBool(int n)
{
    if (n <= 1)
        return 0;
    for (int i = 2; i * i <= n; i++) // sqrt method
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

void main()
{
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    if (isBool(n))
        printf("%d is a prime number.\n", n);
    else
        printf("%d is not a prime number.\n", n);
}
