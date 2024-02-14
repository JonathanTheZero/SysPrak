#include "sig.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void sigHandler(const int signal)
{
    if (signal != SIGUSR1)
    {
        return;
    }
    printf("SIGUSR1 erhalten!\n");
}

void activateHandler()
{
    signal(SIGUSR1, sigHandler);
}