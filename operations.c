#include <stdio.h>
#include <stdlib.h>
#include "operations.h"
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

struct row *createArray(int numOfElements) {
	int i = 0;
	int j;
	//	int array[numOfElements][numOfElements] = { {0 } };
	struct row *array = (struct row *) malloc(numOfElements*(sizeof(struct row)));
	for(i = 0; i< numOfElements; i++)
	{
		array[i] = createRow(numOfElements);
	}
	for(i = 0; i< numOfElements; i++)
	{
		//printf("i is: %d\n",i);
		for(j = 0 ; j < numOfElements ; j++)
		{
			array[i].edgeNums[j] = 0;
		}	 
	}

	//initialize the array to all zero to start with
	//printf("First thingy %d",array[0][0]);
	return array; 
}

void warshalls(struct row *boolMatrix, struct row *warPath, int numOfElements,int numberOfThreads)
{
	int i;
	int j;
	int q;
	//int threadID = 0 ;
	//pid_t pid;
	int offSetValue;
	int z =0 ;
	int leftOver;

	for(i = 0 ; i < numOfElements; i++)
	{
		for(j = 0 ; j < numOfElements ; j++)
		{
			//Copy over the matrix to the path
			warPath[i].edgeNums[j] = boolMatrix[i].edgeNums[j];
		}
	}
        	
	offSetValue = 1 + ((numOfElements-1) / numberOfThreads);
	leftOver = numOfElements % numberOfThreads;
	for(i = 0 ; i < numOfElements; i+=offSetValue)
	{
		// do parrelle and multithreading here
		//offSetValue = 1 + ((numberOfElements-1) / numberOfThreads);
		if(fork() == 0)
		{
			//child
			//lock the mutex
			for(z=1; z < offSetValue ; z++, i++)
			{
				pthread_mutex_lock(warPath[i].lock);

				for(j = 0 ; j < numOfElements ; j++)
				{		
					for(q = 0 ; q < numOfElements ; q++)
					{
						warPath[j].edgeNums[q] = warPath[j].edgeNums[q] || (warPath[j].edgeNums[i] && warPath[i].edgeNums[q]);
					}
					pthread_mutex_unlock(warPath[i].lock);
				}
			}
		}
	}
}


void printGraph(struct row *graph, int numOfElements)
{
	int i;
	int j;
	printf("----------------\n");
	for(i = 0 ; i < numOfElements; i++)
	{
		for(j = 0 ; j < numOfElements ; j++)
		{
			printf("%d",graph[i].edgeNums[j]);
		}
		printf("\n");
	}
	printf("----------------\n");
}



void bagOfTask(struct row *boolMatrix, struct row *warPath, int numOfElements)
{
	int i;
	int j;
	int k;
	struct Queue *tempQ = createQueue(numOfElements);
	for(i = 0 ; i<numOfElements; i++)
	{
		for(j = 0; j < numOfElements; j++)
		{
			warPath[i].edgeNums[j] = boolMatrix[i].edgeNums[j];
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

struct row createRow(int numberOfEdges)
{
	struct  row *newRow = (struct row *) malloc(sizeof(struct row));
	newRow->edgeNums = (int *)malloc(sizeof(int) * numberOfEdges);
	//initialize the lock
	pthread_mutex_init(newRow->lock,NULL);
	return *newRow;
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


void freeAll(struct row *boolMatrix, struct row *warPath,int size)
{
	int i;
	for(i = 0 ; i < size ; i++)
	{
		free(boolMatrix[i].edgeNums);
		free(warPath[i].edgeNums);
	}
	free(boolMatrix);
	free(warPath);
}
