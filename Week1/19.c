#include <stdio.h>

int main()
{
    char str1[] = "Hello, World!";
    int n = sizeof(str1) / sizeof(str1[0]);
    char str2[n + 1];

    int i = 0;
    while (str1[i] != '\0')
    {
        str2[i] = str1[i];
        i++;
    }
    str2[i] = '\0';
    printf("Copied string: %s\n", str2);
}