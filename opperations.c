#include <stdio.h>
#include "main.h"

struct node * createNode(int *name)
{
     struct node *newNode = (struct node*)malloc((sizeof(struct node *)));
     newNode.name = name;

     return newNode;
}
