#define _POSIX_C_SOURCE 200809L

#include "fibonacci.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "pipe.h"
#include <string.h>
#include "sig.h"
#include <signal.h>
#include <sys/types.h>

int fib_main()
{
    int n = 50;
    fibonacci(n);
    return 0;
}

int pipe_main(void)
{
    int fd[2];
    if (pipe(fd) < 0)
    {
        perror("Pipe");
        exit(-1);
    }

    int pid;
    if ((pid = fork()) < 0)
    {
        perror("fork");
        return -1;
    }
    else if (pid == 0)
    {
        close(fd[0]);

        char *str = "Teststring\0";
        int len = strlen(str) + 1;
        char buf[len];
        toUpperChar(str, buf);

        if (write(fd[1], buf, len) != len)
        {
            perror("Write");
            return -1;
        }

        close(fd[1]);
    }
    else
    {
        close(fd[1]);

        char buf[1024];
        read(fd[0], buf, sizeof(buf));

        printf("Received: %s\n", buf);

        close(fd[0]);
    }

    return 0;
}

int main(void)
{
    activateHandler();
    kill(getpid(), SIGUSR1);
    return 0;
}