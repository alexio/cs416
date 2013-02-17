#include <stdio.h>
#include <stdlib.h>
#include "operations.h"
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

struct row *createArray(int numOfElements) {
	int i = 0;
	int j;
	//	int array[numOfElements][numOfElements] = { {0 } };
	struct row *array = (struct row *) malloc(numOfElements*(sizeof(struct row)));
	printf("okay we get here \n");
	for(i = 0; i< numOfElements; i++)
	{
		array[i] = createRow(numOfElements);
	}
	printf("Done with making the rows \n");
	for(i = 0; i< numOfElements; i++)
	{
		//printf("i is: %d\n",i);
		for(j = 0 ; j < numOfElements ; j++)
		{
			array[i].edgeNums[j] = 0;
		}	 
	}

	//initialize the array to all zero to start with
	printf("First thingy %d",array[0].edgeNums[0]);
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
	//int count = 0;
	sem_t mutex;
	 
	sem_init(&mutex,1,0);
	for(i = 0 ; i < numOfElements; i++)
	{
		for(j = 0 ; j < numOfElements ; j++)
		{
			//Copy over the matrix to the path
			warPath[i].edgeNums[j] = boolMatrix[i].edgeNums[j];
		}
	}
        	
	offSetValue = numOfElements/ numberOfThreads;
	leftOver = numOfElements % numberOfThreads;
	printf("Getting here \n");
	printf("original offset value %d  %d  %d\n",offSetValue,numOfElements,numberOfThreads);
	for(i = 0 ; i <= numOfElements;)
	{
		// do parrelle and multithreading here
		//offSetValue = 1 + ((numberOfElements-1) / numberOfThreads);
		//Have to tell if it is the last one
		printf("offset values are : %d\n",i);
		if(fork() == 0)
		{
			printf("Process created \n");
			//child
			//lock the mutex
			for(z=1; z < offSetValue ; z++, i++)
			{
				//pthread_mutex_lock(warPath[i].lock);
				for(j = 0 ; j < numOfElements ; j++)
				{		
					for(q = 0 ; q < numOfElements ; q++)
					{
						warPath[j].edgeNums[q] = warPath[j].edgeNums[q] || (warPath[j].edgeNums[i] && warPath[i].edgeNums[q]);
					}
					//pthread_mutex_unlock(warPath[i].lock);
				}
			}
			sem_post(&mutex);
			printf("Posting to semaphore \n");
			exit(0);
		}
		i+=offSetValue;
	}
	q = 0;
	printf("number of threads \n%d",numberOfThreads);
	while(q < numberOfThreads)
	{
		printf("\nwaiting\n");
		sem_wait(&mutex);
		q++;
		printf("q is %d\n",q); 
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
	//struct Queue *tempQ = createQueue(numOfElements);
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
			/*enqueue(i,k);
			enqueue(tempQ,i);
			enqueue(tempQ,j);*/
		}
	}
}

struct row createRow(int numberOfEdges)
{
	struct  row *newRow = (struct row *) malloc(sizeof(struct row));
	newRow->edgeNums = (int *)malloc(sizeof(int) * numberOfEdges);
	//initialize the lock
	//pthread_mutex_init(newRow->lock,NULL);
	//printf("Making a row \n");
	return *newRow;
}

/*arg should be number of rows*/
struct Queue * createQueue(int elementMax)
{
	struct Queue *queue = (struct Queue *) malloc(sizeof(struct Queue));
	queue->size = 0 ; 
	queue->cap = elementMax;
	queue->head = NULL;
	queue->tail = NULL;
	return queue;
}

struct row *dequeue(struct Queue *queue)
{
	struct row* ptr;
	if(queue->size == 0)
	{
		printf("The queue contains no elements \n");
		return NULL;
	}
	else /*return head of queue rowList*/
	{
		ptr = queue->head->element; /*grab head element*/
		struct rowList* free_head = queue->head; /*move to next elment in the queue*/
		free(free_head);
		
		queue->size--;
		if(queue->size == 0){ /*if queue is empty, set queue list equal to null*/
			queue->head = NULL;
			queue->tail = NULL;
		}
		else{
			queue->head = queue->head->next;
		}
	}
	return ptr;
}

void enqueue(struct Queue * queue, struct row* element)
{
		
	if(queue->size == queue->cap)
	{
		printf("The queue is full cannot add more elements \n");
	}
	else
	{
		/* //increment the size and move the tail to one ahead
		queue->size++;
		queue->tail = queue->tail + 1;
		if (queue->tail == queue->cap)
		{
			queue->tail = 0;
		}
		//add the new element
		queue->elements[queue->tail] = addItem; */
		
		
		struct rowList* rowL;
		
		if(queue->head == NULL){ /*if the queue is empty, set head*/
			rowL = (struct rowList*)malloc(sizeof(struct rowList));
			rowL->element = element;
			queue->head = rowL;
			queue->tail = queue->head;
		}
		else{ /*else add row to end of queue*/
			rowL = (struct rowList*)malloc(sizeof(struct rowList));
			rowL->element = element;
			queue->tail->next = rowL;
		}
		queue->size++;
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
