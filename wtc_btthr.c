#include <stdio.h>
#include <stdlib.h>
#include "operations.h"
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void bagOfTask(struct row* boolMatrix, struct row* warPath, int numOfElements, int thread_num)
{
	int i, j, k;
	struct Queue *tempQ = createQueue(numOfElements);
	struct Params *input = (struct params*)malloc(sizeof(struct Params));
	
	pthread_t tid;
	pthread_attr_t attr; /*thread attrributes*/
	
	for(i = 0 ; i<numOfElements; i++)
	{
		for(j = 0; j < numOfElements; j++)
		{
			warPath[i].edgeNums[j] = boolMatrix[i].edgeNums[j];
		}
		enqueue(tempQ, warPath[i]);
	}
	for(k = 0; k < numOfElements; k++)
	{
		for(i = 0 ; i < numOfElements ; i++)
		{
			while(tempQ->size > 0){
				input->i = i;
				input->k = k;
				input->element = dequeue(tempQ);
				input->numOfElements = numOfElements;
				pthread_create(&tid, NULL, bagIt, input);
			}
		}
	}
}

void *child_laborThread(void *param) {
	int rows, columns,numEdges,k;
	struct Params *attr = (struct Params *)param;
	int fork_count = attr->thread_num;
	numEdges = attr->numEdges;
	k = attr->k;
	// Computation of Warshall’s Transitive Closure
	for (rows = fork_count; rows < numEdges; rows++) { // per row
		for (columns = 0; columns < numEdges; columns++) { // per column
			attr->edge_ptr[rows].edgeNums[columns] = attr->edge_ptr[rows].edgeNums[columns] || (attr->edge_ptr[rows].edgeNums[k] && attr->edge_ptr[k].edgeNums[columns]);
			printf("[%i][%i] = %i\n", rows, columns, attr->edge_ptr[rows].edgeNums[columns]);
		}
		// Child process will loop through every other + (total # process-1) of rows
		rows += attr->thread_num -1;
	}
	return param;
}
/*Initate queue and give each thread a dequeue'd object*/
void ThreadStart(struct row* warPath, int thread_num, int numEdges ){
	struct Params *attr = (struct Params *)calloc(1, sizeof(struct Params));
	attr->edge_ptr = (struct row*)calloc(numEdges, sizeof(struct rows));
	
	struct Queue *queue = createQueue(numOfElements);
	
	int threadCount, k =0;
	pthread_t threads[threadnum];
	
	for(k = 0; k < numEdges; k++){
		for(threadCount = 0;; threadCount < threanum; threadCount++){
			attr->k = k;
			attr->thread_num = threadCount;
			attr->numEdges = numEdges;
			attr->edge_ptr = warPath;
			printf("Launching threads \n");
			pthread_create(&threads[threadCount],NULL,child_laborThread,attr);
		}
		threadCount = 0;
		while(threadCount < threadnum){
			pthread_join(threads[threadCount],NULL);
			threadCount++;
		}
	}
}
void bagOfThreads(struct row* bolMatrix, struct row* warPath, int nmEdges, int numProcess){
	int i, j;
	struct Queue *queue = createQueue(numOfElements);
	sem_t * sem =  calloc(1, sizeof(sem_t));
	/*Initializing semaphor*/
	sem_init(sem, 1, 0);
	
	// Copies over the original 2D array
    for(i = 0 ; i<numEdges; i++)
		for(j = 0; j < numEdges; j++)
			warPath[i].edgeNums[j] = boolMatrix[i].edgeNums[j];
			
	ThreadStart(warPath, numProcess, numEdges, queue);
	return;
}



