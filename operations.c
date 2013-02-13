#include <stdio.h>
#include <stdlib.h>
#include "operations.h";

struct node *createNode(int name) {
     struct node *newNode;
     newNode = (struct node*)malloc((sizeof(struct node* )));
     newNode->name = name;
     return newNode;
}

int createEdge(struct node **array, int currentx,int currenty,struct node *newEdge) {
	//endOfCurrentList->next = newNode;
        //the new node is now the end of the list
	array[currentx][currenty] = newEdge;
	return 0;
}

//Adds a new node to the 2d array
void addNodeToList(struct node **array , struct node *newNode,int currentPos) {
	//endOfList->nextY = newNode;
        //the new node is now the end of the list
        array[currentPos][0] = newNode; 
}

int alreadyInList(/*struct adjLL * head , struct node *checkThisNode*/struct node * matchingNode , struct node **array) {
	//list should just be a pointer to the list should not loose track of the list itself
	/*struct adjLL *ListPointer = head;
	while(ListPointer != NULL)
	{
		if (strcmp(ListPointer->current->name,checkThisNode->name) == 0)
		{
			//We found tht ho
			return 0;
		}
	}
	//Not in the list so add it!
	return -1;*/
	for(int i = 0; i < array.length(); i++)
	{
		if (strcmp(array[i]->name,matchingNode->name) == 0)
		{
			return 0;
		}
	}
	return -1;
}

struct node **createArray(int numOfElements) {
	int i;
	struct node **array = (struct node **) malloc(numOfElements*(sizeof(struct node *));
	for(i = 0; i< numOfElements; i++)
	{
		//array[i] = (struct node *) malloc(numOfElements*(sizeof(struct node));
		for(int j = 0 ; j < numOfElements ; j++)
		{
			array[i][j] = (struct node *) malloc(numOfElements*(sizeof(struct node));
		}	 
	} 
}
