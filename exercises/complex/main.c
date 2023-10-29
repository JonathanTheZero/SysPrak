#include <stdio.h>
#include "complex.h"

int main()
{
    Complex num1 = {5, 3};  // 5 + 3i
    Complex num2 = {1, -4}; // 1 - 4i
    printf("\n");
    printf("Addition: ");
    printComplex(add(num1, num2));
    printf("\n");
    printf("Substraction: ");
    printComplex(substract(num1, num2));
    printf("\n");
    printf("Multiply: ");
    printComplex(multiply(num1, num2));
    printf("\n");
    printf("Divide: ");
    printComplex(divide(num1, num2));
    printf("\n");
    printf("\n");
    return 0;
}