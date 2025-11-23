#include <stdio.h>

void main()
{
    int nums[] = {1, 2, 3, 4, 5};
    int n = sizeof(nums) / sizeof(nums[0]);
    int largest = nums[0];
    for (int i = 0; i < n; i++)
    {
        if (nums[i] > largest)
        {
            largest = nums[i];
        }
    }
    printf("Largest number is %d\n", largest);
}