#include <stdio.h>
#include "main.h"
#include <stdlib.h>


struct node * createNode(int *name)
{
     struct node *newNode;
     newNode = (struct node*)malloc((sizeof(struct node *)));
     newNode->name = name;
     return newNode;
}

struct adjLL * createAdjLL(struct node *firstNode)
{
     struct adjLL *newadjLL = (struct adjLL*)malloc((sizeof(struct adjLL *)));
     newadjLL->current = firstNode;
     return newadjLL;
}

//Adds a connecting node to the end of a list
struct node *createEdge(struct node *endOfCurrentList , struct node *newNode)
{
	endOfCurrentList->next = newNode;
        //the new node is now the end of the list
	return newNode;
}

//Adds a new node to the list of nodes
void addNodeToList(struct adjLL *endOfList , struct node *newNode)
{
	endOfList->nextY = newNode;
        //the new node is now the end of the list
}

int alreadyInList(struct adjLL * head , struct node *checkThisNode)
{
	//list should just be a pointer to the list should not loose track of the list itself
	struct adjLL *ListPointer = head;
	while(ListPointer != NULL)
	{
		if (strcmp(ListPointer->current->name,checkThisNode->name) == 0)
		{
			//We found tht ho
			return 0;
		}
	}
	//Not in the list so add it!
	return -1;
}
