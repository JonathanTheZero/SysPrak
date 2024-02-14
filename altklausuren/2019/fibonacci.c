#include <stdlib.h>
#include <stdio.h>

int _fib(int n);

int *fibonacci(int n)
{
    int *result = malloc((n + 1) * sizeof(int));

    for (int i = 0; i <= n; ++i)
    {
        result[i] = _fib(i);
        printf("%i: %i\n", i, result[i]);
    }

    return result;
}

int _fib(int n)
{
    if (n == 0)
        return 0;
    if (n == 1 || n == 2)
        return 1;
    return _fib(n - 1) + _fib(n - 2);
}