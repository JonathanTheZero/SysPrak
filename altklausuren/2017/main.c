#include "IO.h"
#include <stdio.h>
#include <limits.h>

int min_num(int *arr, int len)
{
    int min = arr[0];
    for (int i = 1; i < len - 1; ++i)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}

int main(void)
{
    int a, b;
    readIO(&a, &b);
    printf("a = %i, b = %i\n", a, b);

    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, -12, 54, 52, 65, 23};
    printf("Minimum: %i\n", min_num(nums, 13));

    return 0;
}
