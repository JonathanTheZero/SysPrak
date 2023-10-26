#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
    FILE *data = fopen("./floats.txt", "r");
    char nums[100];
    float parsedNums[10000];
    if (data == NULL)
    {
        printf("Error while opening file.\n");
        return 1;
    }
    int i = 0;
    while (fgets(nums, 100, data))
    {
        parsedNums[i++] = atof(nums);
    }
    float max = parsedNums[0];
    for (int j = 0; j < 10000; j++)
    {
        if (parsedNums[j] > max)
        {
            max = parsedNums[j];
        }
    }
    printf("Max value is: %f\n", max);
    fclose(data);
    return 0;
}