#include <stdio.h>

void main()
{
    char str[] = "Hello World";
    int length = 0;

    while (str[length] != '\0')
    {
        length++;
    }

    printf("Length of the string %s is %d\n", str, length);
}