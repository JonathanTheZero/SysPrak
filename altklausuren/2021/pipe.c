#include "pipe.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int creat_und_write(int *fd, char *string)
{
    int len = strlen(string) + 1;
    if (pipe(fd) < 0)
    {
        perror("Pipe");
        exit(-1);
    }
    int pid = fork();
    if (pid < 0)
    {
        exit(-1);
    }
    if (pid == 0)
    { // Child
        close(fd[0]);

        if (write(fd[1], string, len) != len)
        {
            perror("Error");
            exit(-1);
        }

        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        char buf[len];
        int n = read(fd[0], buf, len);
        printf("%i: %s\n", n, buf);
        close(fd[0]);
    }
}
