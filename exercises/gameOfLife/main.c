#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <time.h>
#include "board.h"

int main(int argc, char **argv)
{
    srand(time(NULL));
    int size = 16, percentage = 0;

    int opt;
    while ((opt = getopt(argc, argv, ":s:p:")) != -1)
    {
        switch (opt)
        {
        case 's':
            size = atoi(optarg);
            break;
        case 'p':
            percentage = atoi(optarg);
            break;
        case '?':
        default:
            exit(EXIT_FAILURE);
        }
    }

    bool **board;
    fillBoard(&board, size, percentage);
    printf("%i %i\n", size, percentage);
    bool shouldContinue = true;
    while (shouldContinue)
    {
        printBoard(board, size);
        shouldContinue = nextRound(&board, size);
        sleep(1);
    }
    printf("Game has ended:\n");
    printBoard(board, size);
    return 0;
}