#include "logging.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addTry(int newTries, char name[])
{
    FILE *data = fopen("./best.txt", "r+");
    char names[10][100];
    int tries[10];
    if (data == NULL)
    {
        perror("Failed to open file.");
        exit(EXIT_FAILURE);
    }
    char content[100];
    int isName = 1, index = 0;
    while (fgets(content, 100, data))
    {
        if (isName)
        {
            content[strlen(content) - 1] = '\0';
            strcpy(names[index], content);
            isName = 0;
        }
        else
        {
            tries[index++] = atoi(content);
            isName = 1;
        }
    }

    if (newTries >= tries[index - 1] && index > 9)
        return; // new Entry is same or worse as current last

    // find new position
    int newPos = index;
    for (int i = 0; i < index; ++i)
    {
        if (newTries < tries[i])
        {
            newPos = i;
            break;
        }
    }

    // push old entries one back
    for (int i = index - 2; i >= newPos; --i)
    {
        strcpy(names[i + 1], names[i]);
        tries[i + 1] = tries[i];
    }
    // set new entries
    strcpy(names[newPos], name);
    tries[newPos] = newTries;

    data = freopen("./best.txt", "w", data);
    for (int i = 0; i < index; ++i)
    {
        fprintf(data, "%s\n", names[i]);
        fprintf(data, "%i\n", tries[i]);
    }
    fclose(data);
}

void writeToLog(int tries, char name[])
{
    FILE *data = fopen("./log.txt", "a");
    if (data == NULL)
    {
        perror("Failed to open file.");
        exit(EXIT_FAILURE);
    }

    fprintf(data, "%s - %i\n", name, tries);
    fclose(data);
}