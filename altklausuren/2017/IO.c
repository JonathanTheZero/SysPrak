#include "IO.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void readIO(int *a, int *b)
{
    FILE *file = fopen("./IO.conf", "r");
    if (file == NULL)
    {
        perror("Fehler beim Datei öffnen");
        return;
    }

    char buf[1024];
    while (fgets(buf, 1024, file) != NULL)
    {
        char name[50];
        int value;
        sscanf(buf, "%49s = %i\n", name, &value);
        printf("Name: %s, Value: %i\n", name, value);
        if (!strcmp(name, "a"))
        {
            *a = value;
        }
        else if (!strcmp(name, "b"))
        {
            *b = value;
        }
    }
}
