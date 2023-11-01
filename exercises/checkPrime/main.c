#include <stdio.h>
#include <stdbool.h>
#include <gmp.h>
#include "checkPrime.h"

int main()
{
    // int differences = 0;
    // for (int i = 0; i < 2000000; ++i)
    // {
    //     bool iterRes = checkPrimeIterative(i),
    //          pipeRes = checkPrimePipe(i);
    //     if (iterRes != pipeRes)
    //     {
    //         printf("Problem with %i - iterative result: %i, pipe result: %i\n", i, iterRes, pipeRes);
    //         differences++;
    //     }
    // }
    // if (differences == 0)
    // {
    //     printf("Exited without problems.\n");
    // }
    mpz_t num;
    mpz_init(num);
    mpz_set_ui(num, 4093082899);
    bool result = checkPrimeMultiThreaded(num, 5);

    if (result)
        gmp_printf("%Zd is a prime number!\n", num);
    else
        gmp_printf("%Zd is not a prime number!\n", num);
    // printf("Iterative result: %i\n", checkPrimeIterative(11));
    // printf("Pipe result: %i\n", checkPrimePipe(11));
    return 0;
}