#include <stdio.h>

int power(int base, int exp)
{
    int result = 1;
    for (int i = 0; i < exp; i++)
    {
        result *= base;
    }
    return result;
}

void main()
{
    int base, exp;
    printf("Enter base and exponent: ");
    scanf("%d %d", &base, &exp);

    int result = power(base, exp);
    printf("%d raised to the power of %d is: %d\n", base, exp, result);
}
