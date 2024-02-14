#include <stdio.h>
#include "IO.h"
#include <stdlib.h>
#include <string.h>

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
        char paramName[50], paramValue[50];
        sscanf(line, "%49s = %49s", paramName, paramValue);
        if (!strcmp(paramName, "a"))
        {
            *a = atoi(paramValue);
        }
        if (!strcmp(paramName, "b"))
        {
            *b = atoi(paramValue);
        }
    }

    fclose(file);
}