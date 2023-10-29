#include "matrixBib.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <stdbool.h>

matrix initMatrix(unsigned int breite, unsigned int hoehe)
{
    double *eintraege = malloc(breite * hoehe * sizeof(double));
    if (eintraege == NULL)
    {
        perror("Couldn't reserve memory for matrix.");
        exit(EXIT_FAILURE);
    }
    matrix mat = {.breite = breite, .hoehe = hoehe, .eintraege = eintraege};
    return mat;
}

matrix initMatrixZero(unsigned int breite, unsigned int hoehe)
{
    matrix mat = initMatrix(breite, hoehe);
    for (int i = 0; i < breite * hoehe; ++i)
    {
        mat.eintraege[i] = 0;
    }
    return mat;
}

matrix initMatrixRand(unsigned int breite, unsigned int hoehe)
{
    matrix mat = initMatrix(breite, hoehe);
    for (int i = 0; i < breite * hoehe; ++i)
    {
        mat.eintraege[i] = rand() % 1000;
    }
    return mat;
}

matrix copyMatrix(matrix toCopy)
{
    matrix newMat = initMatrix(toCopy.breite, toCopy.hoehe);
    for (int i = 0; i < toCopy.breite * toCopy.hoehe; ++i)
    {
        newMat.eintraege[i] = toCopy.eintraege[i];
    }
    return newMat;
}

void freeMatrix(matrix toDestroy)
{
    free(toDestroy.eintraege);
}

double getEntryAt(matrix a, unsigned int xPos, unsigned int yPos)
{
    int absolutePos = (yPos - 1) * a.breite + xPos - 1;
    if (absolutePos > a.breite * a.hoehe)
        return DBL_MAX;
    return a.eintraege[absolutePos];
}

bool setEntryAt(matrix a, unsigned int xPos, unsigned int yPos, double value)
{
    int absolutePos = (yPos - 1) * a.breite + xPos - 1; // -1 for Array index
    if (absolutePos > a.breite * a.hoehe)
        return false;
    a.eintraege[absolutePos] = value;
    return true;
}

void prettyPrint(matrix a)
{
    printf("\n");
    for (int i = 0; i < a.breite * a.hoehe; i++)
    {
        printf("|%f", a.eintraege[i]);
        if ((i + 1) % a.breite == 0)
        {
            printf("|\n");
        }
    }
    printf("\n");
}

matrix addMatrix(matrix a, matrix b)
{
    if (a.breite != b.breite || a.hoehe != b.hoehe)
    {
        return initMatrix(0, 0);
    }
    matrix result = initMatrix(a.breite, a.hoehe);
    for (int i = 0; i < a.breite * a.hoehe; ++i)
    {
        result.eintraege[i] = a.eintraege[i] + b.eintraege[i];
    }
    return result;
}

matrix subMatrix(matrix a, matrix b)
{
    if (a.breite != b.breite || a.hoehe != b.hoehe)
    {
        return initMatrix(0, 0);
    }
    matrix result = initMatrix(a.breite, a.hoehe);
    for (int i = 0; i < a.breite * a.hoehe; ++i)
    {
        result.eintraege[i] = a.eintraege[i] - b.eintraege[i];
    }
    return result;
}

matrix multMatrix(matrix a, matrix b)
{
    if (a.breite != b.hoehe)
    {
        return initMatrix(0, 0);
    }
    matrix result = initMatrix(b.breite, a.hoehe);
    for (int x = 1; x <= result.breite; ++x)
    {
        for (int y = 1; y <= result.hoehe; ++y)
        {
            double sum = 0;
            for (int j = 1; j <= result.breite; ++j)
            {
                sum += getEntryAt(a, j, y) * getEntryAt(b, x, j);
            }
            setEntryAt(result, x, y, sum);
        }
    }
    return result;
}

matrix transposeMatrix(matrix a)
{
    matrix result = initMatrix(a.hoehe, a.breite);
    for (int x = 1; x <= result.breite; ++x)
    {
        for (int y = 1; y <= result.hoehe; ++y)
        {
            setEntryAt(result, x, y, getEntryAt(a, y, x));
        }
    }
    return result;
}