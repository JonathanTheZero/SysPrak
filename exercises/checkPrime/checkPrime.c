#include "checkPrime.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>

bool checkPrimeInInterval(unsigned long long prim, unsigned long long start, unsigned long long end);

bool checkPrimeIterative(unsigned long long prim)
{
    if (prim < 0)
    {
        perror("Number should be positive.");
        exit(EXIT_FAILURE);
    }
    if (prim < 2 || prim % 2 == 0)
        return false;

    for (unsigned long long i = 3; i < sqrt(prim); i += 2)
    {
        if (prim % i == 0)
        {
            return false;
        }
    }

    return true;
}

bool checkPrimePipe(unsigned long long prim)
{
    if (prim < 0)
    {
        perror("Number should be positive.");
        exit(EXIT_FAILURE);
    }
    if (prim < 2 || prim % 2 == 0)
        return false;

    pid_t pid;
    int fd[2];
    if (pipe(fd) < 0)
    {
        perror("Error on creating pipe");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0)
    {
        perror("Error on fork().");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0) // parent process
    {
        close(fd[1]); // Close writing
        bool isPrime = checkPrimeInInterval(prim, 3, sqrt(prim) / 2);
        bool *childResult = NULL;
        printf("Test\n");
        int n = read(fd[0], childResult, 1);
        printf("n: %i, result: %i\n", n, *childResult);
    }
    else // child process
    {
        close(fd[0]); // close reading
        bool isPrime = checkPrimeInInterval(prim, sqrt(prim) / 2 + 1, sqrt(prim));
        if (write(pid, isPrime, 1) != 1)
        {
            perror("Error on writing to parent.");
            exit(EXIT_FAILURE);
        }
    }

    return true;
}

bool checkPrimeInInterval(unsigned long long prim, unsigned long long start, unsigned long long end)
{
    if (start % 2 == 0)
        start++;
    for (unsigned long long i = start; i < end; i += 2)
    {
        if (prim % i == 0)
        {
            return false;
        }
    }
    return true;
}
