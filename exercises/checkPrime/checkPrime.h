#include <stdbool.h>
#include <gmp.h>

bool checkPrimeIterative(unsigned long long prim);
bool checkPrimePipe(unsigned long long prim);
bool checkPrimeMultiThreaded(mpz_t prim, int threads);