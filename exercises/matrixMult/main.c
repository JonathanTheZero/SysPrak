#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN 0
#define MAX 9
#define N 3

int randomValue();
void initializeMatrices(int mat1[][N], int mat2[][N]);
void printMatrix(int mat[N][N]);
void multiplyMatrices(int mat1[][N], int mat2[][N], int result[][N]);

int main()
{
    srand(time(NULL));
    int matrix1[N][N], matrix2[N][N], result[N][N];
    initializeMatrices(matrix1, matrix2);
    printf("Matrix1:\n");
    printMatrix(matrix1);
    printf("Matrix2:\n");
    printMatrix(matrix2);
    multiplyMatrices(matrix1, matrix2, result);
    printf("Result:\n");
    printMatrix(result);
    return 0;
}

void multiplyMatrices(int mat1[][N], int mat2[][N], int result[][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int sum = 0;
            for (int k = 0; k < N; k++)
            {
                sum += (mat1[i][k]) * (mat2[k][j]);
            }
            result[i][j] = sum;
        }
    }
}

void initializeMatrices(int mat1[][N], int mat2[][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            mat1[i][j] = randomValue();
            mat2[i][j] = randomValue();
        }
    }
}

void printMatrix(int mat[N][N])
{
    for (int i = 0; i < (2 * N) + 1; i++)
    {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < N; i++)
    {
        printf("|");
        for (int j = 0; j < N; j++)
        {
            printf("%d|", mat[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < (2 * N) + 1; i++)
    {
        printf("-");
    }
    printf("\n");
}

int randomValue()
{
    return (rand() % (MAX + 1 - MIN)) + MIN;
}