#include <stdio.h>
#include <stdbool.h>
#include "checkPrime.h"

int main()
{
    int differences = 0;
    for (int i = 0; i < 2000000; ++i)
    {
        bool iterRes = checkPrimeIterative(i),
             pipeRes = checkPrimePipe(i);
        if (iterRes != pipeRes)
        {
            printf("Problem with %i - iterative result: %i, pipe result: %i\n", i, iterRes, pipeRes);
            differences++;
        }
    }
    if (differences == 0)
    {
        printf("Exited without problems.\n");
    }
    // printf("Iterative result: %i\n", checkPrimeIterative(11));
    // printf("Pipe result: %i\n", checkPrimePipe(11));
    return 0;
}