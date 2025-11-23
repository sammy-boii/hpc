#include <stdio.h>

void main()
{
    int a, b, c;
    printf("Enter 3 numbers: ");

    scanf("%d %d %d", &a, &b, &c);

    if (a > b && a > c)
    {
        printf("%d is the largest number\n", a);
    }
    else if (b > a && b > c)
    {
        printf("%d is the largest number\n", b);
    }
    else if (c > a && c > b)
    {
        printf("%d is the largest number\n", c);
    }
    else
    {
        printf("All numbers are equal\n");
    }
}