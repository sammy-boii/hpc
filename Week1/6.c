#include <stdio.h>

void main()
{
    char vowels[] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    int n = sizeof(vowels) / sizeof(vowels[0]);
    char ch;
    int isVowel = 0;

    printf("Enter a character: ");
    scanf("%c", &ch);
    for (int i = 0; i < n; i++)
    {
        if (ch == vowels[i])
        {
            printf("%c is a vowel\n", ch);
            isVowel = 1;
            break;
        }
    }
    if (!isVowel)
    {
        printf("%c is a consonant\n", ch);
    }
}