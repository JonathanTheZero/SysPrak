#include "ll.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void addElementEnd(ll_t *list, int value)
{
	ll_t *newEntry = malloc(sizeof(ll_t));
	newEntry->val = value;
	if (list == NULL)
		return;
	while (list->next != NULL)
	{
		list = list->next;
	}
	list->next = newEntry;
}

void addElementFront(ll_t **list, int value)
{
	ll_t *newEntry = malloc(sizeof(ll_t));
	newEntry->val = value;
	if (list == NULL)
		return;
	newEntry->next = *list;
	*list = newEntry;
	// printf("TEst: %i\n", (*list)->val);
}

void printElements(ll_t *list)
{
	while (list->next != NULL)
	{
		printf("%i->", list->val);
		list = list->next;
	}
	printf("%i\n", list->val);
}

void freeList(ll_t *list)
{
	ll_t *tmp;
	while (list != NULL)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

int countElements(ll_t *list)
{
	if (list == NULL)
		return 0;

	int counter = 1;

	while (list->next != NULL)
	{
		counter++;
		list = list->next;
	}
	return counter;
}

void copyListToArray(ll_t *list, int *array, int length)
{
	for (int i = 0; i < length; i++)
	{
		array[i] = list->val;
		list = list->next;
	}
}
