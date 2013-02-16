#include <stdio.h>
#include <stdlib.h>
#include "operations.h"
#include <math.h>
#include <string.h>


int **createArray(int numOfElements) {
	int i = 0;
	int j;
//	int array[numOfElements][numOfElements] = { {0 } };
	int **array = (int **) malloc(numOfElements*(sizeof(int *)));
	for(i = 0; i< numOfElements; i++)
	{
		//for(j = 0 ; j < numOfElements ; j++)
		//{
			array[i] = (int *) calloc(numOfElements,(sizeof(int)));
		//}	 
	}
	for(i = 0; i< numOfElements; i++)
	{
		//printf("i is: %d\n",i);
		for(j = 0 ; j < numOfElements ; j++)
		{
			array[i][j] = 0;
		}	 
	}

	//initialize the array to all zero to start with
	//printf("First thingy %d",array[0][0]);
	return array; 
}

void warshalls(int **boolMatrix, int **warPath, int numOfElements)
{
	int i;
	int j;
	int q;

	for(i = 0 ; i < numOfElements; i++)
	{
		for(j = 0 ; j < numOfElements ; j++)
		{
			//Copy over the matrix to the path
			warPath[i][j] = boolMatrix[i][j];
		}
	}

	for(i = 0 ; i < numOfElements; i++)
	{
		for(j = 0 ; j < numOfElements ; j++)
		{
			if (warPath[i][j] == 1)
			{
				for(q = 0 ; q < numOfElements ; q++)
				{
					if (warPath[j][q] == 1)
					{
						warPath[i][q] = 1;
					}
				}
			}
		}
	}
}


void printGraph(int **graph, int numOfElements)
{
	int i;
	int j;
	printf("----------------\n");
	for(i = 0 ; i < numOfElements; i++)
	{
		for(j = 0 ; j < numOfElements ; j++)
		{
			printf("%d",graph[i][j]);
		}
		printf("\n");
	}
	printf("----------------\n");
}



void bagOfTask(int **boolMatrix, int **warPath, int numOfElements)
{
	int i;
	int j;
	int k;
	struct Queue *tempQ = createQueue(numOfElements);
	for(i = 0 ; i<numOfElements; i++)
	{
		for(j = 0; j < numOfElements; j++)
		{
			warPath[i][j] = boolMatrix[i][j];
		}
	}
	for(k = 0; k < numOfElements ; k++)
	{
		for(i = 0 ; i < numOfElements ; i++)
		{
			//enqueue(i,k);
			enqueue(tempQ,i);
			enqueue(tempQ,j);
		}
	}
}

struct Queue * createQueue(int elementMax)
{
	struct Queue *queue = (struct Queue *) malloc(sizeof(struct Queue));
	queue->elements = (int *)malloc(sizeof(int) * elementMax);
	queue->size = 0 ; 
	queue->cap = elementMax;
	queue->head = 0;
	queue->tail = -1;
	return queue;
}


void dequeue(struct Queue *queue)
{
	if(queue->size == 0)
	{
		printf("The queue contains no elements \n");
		return;
	}
	else
	{
		//Decrement the size and move the head up by one to take the place of the removed element
		queue->size--;
		queue->head++;
		if(queue->head == queue->cap)
		{
			queue->head = 0;
		}
	}
	return;
}

void enqueue(struct Queue * queue, int addItem)
{
	if(queue->size == queue->cap)
	{
		printf("The queue is full cannot add more elements \n");
	}
	else
	{
		//increment the size and move the tail to one ahead
		queue->size++;
		queue->tail = queue->tail + 1;
		if (queue->tail == queue->cap)
		{
			queue->tail = 0;
		}
		//add the new element
		queue->elements[queue->tail] = addItem;
	}
}


void freeAll(int **boolMatrix, int **warPath,int size)
{
	int i;
	for(i = 0 ; i < size ; i++)
	{
		free(boolMatrix[i]);
		free(warPath[i]);
	}
	free(boolMatrix);
	free(warPath);
}
