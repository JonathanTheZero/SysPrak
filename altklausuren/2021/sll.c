#include "sll.h"
#include <stdlib.h>
#include <stdio.h>

void add_Element(struct node *list, int x)
{
    struct node *tmp = list;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    struct node *newEl = malloc(sizeof(struct node));
    newEl->x = x;
    newEl->next = NULL;
    tmp->next = newEl;
}

void printList(struct node *first)
{
    struct node *tmp = first;
    printf("%i, ", tmp->x);
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
        printf("%i, ", tmp->x);
    }

    printf("\n");
}