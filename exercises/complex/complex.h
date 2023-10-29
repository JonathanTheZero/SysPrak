#ifndef My_COMPLEX
#define My_COMPLEX

typedef struct __compl
{
    double real;
    double imaginary;
} Complex;

Complex add(Complex num1, Complex num2);
Complex substract(Complex num1, Complex num2);
Complex multiply(Complex num1, Complex num2);
Complex divide(Complex num1, Complex num2);

void printComplex(Complex num);

#endif