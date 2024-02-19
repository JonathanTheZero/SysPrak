#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "IO.h"
#include "sll.h"
#include "pipe.h"

int primeNumber_main(int argc, char **argv)
{
    if (argc < 1)
    {
        return -1;
    }

    int number = atoi(argv[1]);
    if (number < 2 || number > 10000)
    {
        return -1;
    }

    if (number % 2 == 0)
    {
        printf("0\n");
        return -1;
    }

    for (int i = 3; i * i < number; i += 2)
    {
        if (number % i == 0)
        {
            printf("0\n");
            return -1;
        }
    }
    printf("1\n");
    return 0;
}

int main(int argc, char **argv)
{
    int a, b;
    getAB(&a, &b);
    printf("A: %i B: %i\n", a, b);
}

int ll_main(void)
{
    struct node a;
    a.x = 10;
    a.next = NULL;
    struct node first;
    first.x = 15;
    first.next = &a;
    printList(&first);
    add_Element(&first, 7);
    printList(&first);
    return 0;
}

int pipe_main(void){
    int fd[2];
    int result = creat_und_write(fd, "Hallo Welt\0");
}
