#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "./matrixBib.h"

int main()
{
    srand(time(NULL));

    matrix mat = initMatrixRand(4, 3);
    prettyPrint(mat);
    setEntryAt(mat, 2, 3, -5);
    printf("%f\n", getEntryAt(mat, 4, 3));
    prettyPrint(mat);
    prettyPrint(transposeMatrix(mat));

    return 0;
}