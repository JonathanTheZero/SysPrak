#include <stdio.h>
#include "IO.h"
#include <stdlib.h>

void getAB(int *a, int *b)
{
    FILE *file = fopen("./io.conf", "r");

    if (file == NULL)
    {
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char key;
        int value;
        sscanf(line, " %c = %i ", &key, &value);
        printf("Key: %c, Value: %i\n", key, value);
        if (key == '\n') continue;
        if (key == 'a')
        {
            *a = value;
        }
        if (key == 'b')
        {
            *b = value;
        }
    }

    fclose(file);
}
