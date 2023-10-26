#include <stdbool.h>
#include <stdio.h>
#include "board.h"

void printBoard(bool **board, int rows)
{

    for (int i = 0; i < (2 * rows) + 1; ++i)
    {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < rows; ++i)
    {
        printf("|");
        for (int j = 0; j < rows; ++j)
        {
            printf(board[i][j] ? "*|" : "-|");
        }
        printf("\n");
    }
    for (int i = 0; i < (2 * rows) + 1; ++i)
    {
        printf("-");
    }
    printf("\n");
}

void fillBoard(bool ***board, int rows, int percentage)
{
    *board = malloc(rows * sizeof(bool *));
    for (int i = 0; i < rows; ++i)
    {
        (*board)[i] = malloc(sizeof(bool));
        for (int j = 0; j < rows; ++j)
        {
            (*board)[i][j] = (rand() % 100 < percentage);
        }
    }
}

bool isAliveNextRound(bool **board, int x, int y, int rows)
{
    int neighboursSummed = 0;
    // if (x > 0 && x < rows && y > 0 && y < rows)
    //     neighboursSummed = board[x - 1][y] + board[x][y + 1] + board[x + 1][y] + board[x][y - 1];
    // else if (x == 0 && y == 0)
    //     neighboursSummed = board[x][y + 1] + board[x + 1][y];
    // else if (x == rows && y == rows)
    //     neighboursSummed = board[x][y - 1] + board[x - 1][y];
    // else if (x == 0)
    //     neighboursSummed = board[x][y + 1] + board[x][y - 1] + board[x + 1][y];
    // else if (y == 0)
    //     neighboursSummed = board[x - 1][y] + board[x + 1][y] + board[x][y + 1];
    // else if (x == rows)
    //     neighboursSummed = board[x][y + 1] + board[x][y - 1] + board[x - 1][y];
    // else if (y == rows)
    //     neighboursSummed = board[x - 1][y] + board[x + 1][y] + board[x][y - 1];
    if (x >= 0 && x < rows && y >= 0 && y < rows)
    {
        if (x > 0)
            neighboursSummed += board[x - 1][y];
        if (y < rows - 1)
            neighboursSummed += board[x][y + 1];
        if (x < rows - 1)
            neighboursSummed += board[x + 1][y];
        if (y > 0)
            neighboursSummed += board[x][y - 1];
    }

    if (!board[x][y] && neighboursSummed == 3 || (board[x][y] && (neighboursSummed == 2 || neighboursSummed == 3)))
    {
        return true;
    }
    return false;
}

bool nextRound(bool ***board, int rows)
{
    bool hasChanged = false;
    bool **newData = NULL;
    fillBoard(&newData, rows, 0);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < rows; ++j)
        {
            bool newValue = isAliveNextRound(*board, i, j, rows);
            if (newValue != (*board)[i][j])
                hasChanged = true;
            newData[i][j] = newValue;
        }
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < rows; ++j)
        {
            (*board)[i][j] = newData[i][j];
        }
    }
    // free temp board memory
    for (int i = 0; i < rows; ++i)
    {
        free(newData[i]);
    }
    free(newData);

    return hasChanged;
}