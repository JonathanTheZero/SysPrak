#include <stdio.h>
#include <unistd.h>
#include "matrixBib.h"

int main(int argc, char* argv[]) {

    for (int i = 0; i < argc; i++)
        printf("argv[%d] = %s\n", i, argv[i]);


    int opt;
    while((opt = getopt(argc, argv, ":")) != -1)
    {
        printf("%c", opt);
    }
    return 0;
}

float convert(char from, char to, float value){
    if(from == to) return value;
}