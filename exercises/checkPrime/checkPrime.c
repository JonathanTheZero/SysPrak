#include "checkPrime.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <gmp.h>
#include <time.h>

bool checkPrimeInInterval(unsigned long long prim, unsigned long long start, unsigned long long end);
void *checkPrimeInIntervalGmp(void *args);

bool checkPrimeIterative(unsigned long long prim)
{
    if (prim < 0)
    {
        perror("Number should be positive.");
        exit(EXIT_FAILURE);
    }
    if (prim < 2 || prim % 2 == 0)
        return false;

    for (unsigned long long i = 3; i <= sqrt(prim); i += 2)
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

    if (prim == 3)
        return true;

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
        bool isPrime = checkPrimeInInterval(prim, 3, sqrt(prim) / 2),
             childResult = 0;
        read(fd[0], &childResult, sizeof(bool));
        if (waitpid(pid, NULL, 0) < 0)
        {
            perror("Error while waiting on child process!");
            exit(EXIT_FAILURE);
        }
        close(fd[0]);
        return isPrime && childResult;
    }
    else // child process
    {
        close(fd[0]); // close reading
        bool isPrime = checkPrimeInInterval(prim, sqrt(prim) / 2 + 1, sqrt(prim) + 1);
        if (write(fd[1], &isPrime, sizeof(bool)) != sizeof(bool))
        {
            perror("Error on writing to parent.");
            exit(EXIT_FAILURE);
        }
        close(fd[1]);
        exit(EXIT_SUCCESS);
    }
}

bool checkPrimeInInterval(unsigned long long prim, unsigned long long start, unsigned long long end)
{
    if (start % 2 == 0)
        start++;
    // printf("Prime: %llu, start: %llu, end: %llu\n", prim, start, end);
    for (unsigned long long i = start; i <= end; i += 2)
    {
        if (prim % i == 0)
        {
            return false;
        }
    }
    return true;
}

struct ThreadArgs
{
    mpz_t prim;
    mpz_t start;
    mpz_t end;
};

bool checkPrimeMultiThreaded(mpz_t prim, int threadCount)
{
    mpz_t modResult;
    mpz_init(modResult);
    mpz_mod_ui(modResult, prim, 2); // modResult = prim % 2
    if (mpz_cmp_ui(modResult, 0) == 0 || mpz_cmp_ui(prim, 3) == -1)
    {
        return false;
    }

    pthread_t *threads = malloc(threadCount * sizeof(pthread_t));
    mpz_t *starts = malloc(threadCount * sizeof(mpz_t));
    mpz_t *ends = malloc(threadCount * sizeof(mpz_t));
    mpz_init(starts[0]);
    mpz_init(ends[0]);

    mpz_t totalStart, totalEnd;
    mpz_init(totalStart);
    mpz_init(totalEnd);

    mpz_set_ui(totalStart, 3);
    mpz_root(totalEnd, prim, 2);                   // totalEnd = sqrt(prim)
    mpz_add_ui(totalEnd, totalEnd, 1);             // totalEnd += 1
    mpz_set(starts[0], totalStart);                // currentStart = totalStart
    mpz_cdiv_q_ui(ends[0], totalEnd, threadCount); // currentEnd = totalEnd / threadCount
    mpz_add_ui(ends[0], ends[0], 1);               // currentEnd += 1;

    for (int i = 1; i < threadCount; ++i)
    {
        mpz_init(starts[i]);
        mpz_init(ends[i]);
        mpz_add_ui(starts[i], ends[i - 1], 1);  // currentStart = currentEnd + 1
        mpz_add(ends[i], ends[i - 1], ends[0]); // CurrentEnd = PreviousEnd + ends[0] -> in i-th call CurrentEnd is i * (totalEnd/threadCount);
        mpz_add_ui(ends[i], ends[i], 1);        // CurrentEnd += 1
    }

    for (int i = 0; i < threadCount; ++i)
    {
        struct ThreadArgs *threadArgs = malloc(sizeof(struct ThreadArgs));
        mpz_init(threadArgs->prim);
        mpz_init(threadArgs->start);
        mpz_init(threadArgs->end);

        mpz_set(threadArgs->prim, prim);
        mpz_set(threadArgs->start, starts[i]);
        mpz_set(threadArgs->end, ends[i]);

        pthread_create(&(threads[i]), NULL, checkPrimeInIntervalGmp, threadArgs);
        // sleep(1);
        //   gmp_printf("CurrStart: %Zd, CurrEnd: %Zd\n", currentStart, currentEnd);
    }

    bool totalResult = true;
    for (int i = 0; i < threadCount; ++i)
    {
        void *result;
        pthread_join(threads[i], &result);
        totalResult &= (bool)result;
    }

    return totalResult;
}

void *checkPrimeInIntervalGmp(void *args)
{
    struct ThreadArgs *threadArgs = (struct ThreadArgs *)args;
    void *result = malloc(sizeof(bool));

    // gmp_printf("%Zd and %Zd and %Zd\n", prim, start, end);
    for (; mpz_cmp(threadArgs->start, threadArgs->end) < 1; mpz_add_ui(threadArgs->start, threadArgs->start, 2))
    {
        mpz_t modResult;
        mpz_init(modResult);
        mpz_mod(modResult, threadArgs->prim, threadArgs->start);
        if (mpz_cmp_ui(modResult, 0) == 0)
        {
            result = false;
            return result;
        }
    }

    result = true;
    return result;
}
