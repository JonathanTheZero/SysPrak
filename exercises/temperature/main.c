#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>

float convert(char from, char to, float value)
{
    if (from == to)
        return value;

    float valInC = 0;
    switch (from)
    {
    case 'C':
        valInC = value;
        break;
    case 'D':
        valInC = (100 - value) * 2 / 3;
        break;
    case 'F':
        valInC = (value - 32) * 5 / 9;
        break;
    case 'K':
        valInC = value - 273.15;
        break;
    case 'R':
        valInC = (value * 5 / 9) - 273.15;
        break;
    default:
        printf("Unknown input unit.");
        exit(EXIT_FAILURE);
    }

    switch (to)
    {
    case 'C':
        return valInC;
    case 'D':
        return (100 - valInC) * 1.5;
    case 'F':
        return (100 * 1.8) + 32;
    case 'K':
        return valInC + 273.15;
    case 'R':
        return valInC * 1.8 + 273.15;
    default:
        printf("Unknown output unit.");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    char *from = NULL, *to = NULL;
    float value;

    int opt;
    while ((opt = getopt(argc, argv, ":f:t:v:")) != -1)
    {
        switch (opt)
        {
        case 'f':
            from = optarg;
            break;
        case 't':
            to = optarg;
            break;
        case 'v':
            value = atof(optarg);
            break;
        case '?':
        default:
            exit(EXIT_FAILURE);
        }
    }

    if (from != NULL && to != NULL)
    {
        float result = convert(*from, *to, value);
        printf("%f\n", result);
    }

    return 0;
}