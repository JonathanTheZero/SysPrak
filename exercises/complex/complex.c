#include "complex.h"
#include <stdio.h>
#include <stdlib.h>

Complex add(Complex num1, Complex num2)
{
    Complex result = {
        .real = num1.real + num2.real,
        .imaginary = num1.imaginary + num2.imaginary};
    return result;
}

Complex substract(Complex num1, Complex num2)
{
    Complex result = {
        .real = num1.real - num2.real,
        .imaginary = num1.imaginary - num2.imaginary};
    return result;
}

Complex multiply(Complex num1, Complex num2)
{
    Complex result = {
        .real = num1.real * num2.real - num1.imaginary * num2.imaginary,
        .imaginary = num1.real * num2.imaginary + num1.imaginary * num2.real};

    return result;
}

Complex divide(Complex num1, Complex num2)
{
    double divisor = num2.real * num2.real + num2.imaginary * num2.imaginary;
    if (divisor == 0)
    {
        perror("Division by 0 is not allowed.");
        exit(EXIT_FAILURE);
    }
    Complex result = {
        .real = (num1.real * num2.real + num1.imaginary * num2.imaginary) / divisor,
        .imaginary = (num1.imaginary * num2.real - num1.real * num2.imaginary) / divisor};
    return result;
}

void printComplex(Complex num)
{
    if (num.imaginary < 0)
        printf("%f-i%f", num.real, -1 * num.imaginary);
    else
        printf("%f+i%f", num.real, num.imaginary);
}