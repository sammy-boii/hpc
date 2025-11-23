#include <stdio.h>
#include <string.h> // for strlen

void main()
{
    char str[] = "Hello, World!";

    // NOTE: sizeof(str) gives the size including the null terminator (14)

    // strlen(str) gives the length excluding the null terminator

    int n = sizeof(str) / sizeof(str[0]);

    char reversed[n];

    for (int i = 0; i < n; i++)
    {
        reversed[i] = str[n - i - 2]; // exclude null terminator
    }

    reversed[n - 1] = '\0'; // Null-terminate the reversed string

    printf("Reversed String: %s\n", reversed);
}