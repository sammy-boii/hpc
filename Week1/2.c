#include <stdio.h>

int main()
{

    // swapping with three variables

    int a = 5, b = 10, c;

    printf("Before swapping: a = %d, b = %d\n", a, b);
    c = a;
    a = b;
    b = c;
    printf("After swapping: a = %d, b = %d\n", a, b);

    // swapping without third variable

    a = 5, b = 10;
    printf("Before swapping: a = %d, b = %d\n", a, b);

    a = a ^ b; // a now becomes 15 (1111 in binary)
    b = a ^ b; // b becomes 5 (0101 in binary)
    a = a ^ b; // a becomes 10 (1010 in binary)

    printf("After swapping: a = %d, b = %d\n", a, b);
}