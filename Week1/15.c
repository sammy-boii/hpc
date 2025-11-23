#include <stdio.h>

int *sort_asc(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return arr;
}

int *sort_desc(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    return arr;
}

void main()
{
    int arr[] = {4, 1, 5, 7, 9, 8, 6, 11, 44, 100};
    int n = sizeof(arr) / sizeof(arr[0]);

    int *asc = sort_asc(arr, n);
    int *desc = sort_desc(arr, n);

    printf("Sorted array in ascending order: \n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", asc[i]);
    }

    printf("\nSorted array in descending order: \n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", desc[i]);
    }
}