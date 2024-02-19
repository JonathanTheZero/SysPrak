typedef struct ll
{
	int val;
	struct ll *next;
} ll_t;

void addElementEnd(ll_t *list, int value);
void addElementFront(ll_t **list, int value);
void printElements(ll_t *list);

void freeList(ll_t *list);

int countElements(ll_t *list);
void copyListToArray(ll_t *list, int *array, int length);
