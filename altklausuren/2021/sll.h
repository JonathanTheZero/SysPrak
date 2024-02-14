struct node
{
    int x;
    struct node *next;
};

void add_Element(struct node *list, int x);
void printList(struct node *first);