#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int getFileContents(char *filename, float **nums);
void findMaxNum(float *nums, int length);

int main()
{
    float *nums = NULL;
    int length = getFileContents("./floats.txt", &nums);
    if (length > 0)
    {
        findMaxNum(nums, length);
    }
    else
    {
        perror("Couldn't parse array!");
        return 1;
    }
    return 0;
}

int getFileContents(char *filename, float **nums)
{
    FILE *data = fopen("./floats.txt", "r");
    if (data == NULL)
    {
        perror("Failed to open file");
        return -1;
    }

    int i = 0;
    char content[100];
    while (fgets(content, 100, data))
    {
        float value = atof(content);
        float *tmp_ptr = realloc(*nums, (i + 1) * sizeof(float));
        if (tmp_ptr == NULL)
        {
            perror("Memory allocation failed");
            free(nums);
            fclose(data);
            return -1;
        }
        *nums = tmp_ptr;
        (*nums)[i++] = value;
    }
    fclose(data);
    return i;
}

void findMaxNum(float *nums, int length)
{
    float max = nums[0];
    for (int i = 1; i < length; ++i)
    {
        if (nums[i] > max)
        {
            max = nums[i];
        }
    }
    printf("The maximum number is: %f\n", max);
}