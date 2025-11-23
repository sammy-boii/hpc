#include <stdio.h>

void main()
{
    int n, reversed = 0;

    printf("Enter a number: ");
    scanf("%d", &n);

    while (n > 0)
    {
        int digit = n % 10;
        n /= 10;
        reversed = reversed * 10 + digit;
    }
    printf("Reversed Number: %d\n", reversed);
}