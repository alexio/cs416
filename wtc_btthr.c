#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "operations.h"

void *child_laborer(void *param) {
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
void ThreadStart(struct Queue * queue, struct row* warPath, int thread_num, int numEdges ){
	struct Params *attr = (struct Params *)calloc(1, sizeof(struct Params));
	attr->edge_ptr = (struct row*)calloc(numEdges, sizeof(struct row));
	
	int threadCount, k =0;
	pthread_t threads[thread_num];/*Thread ids*/
	
	for(k = 0; k < numEdges; k++){
		/*Create threads*/
		for(threadCount = 0; threadCount < thread_num; threadCount++){
			attr->k = k;
			attr->thread_num = threadCount;
			attr->numEdges = numEdges;
			attr->edge_ptr = warPath;
			printf("Launching threads \n");
			pthread_create(&threads[threadCount],NULL,child_laborer,attr);
		}
		threadCount = 0;
		while(threadCount < thread_num){
			pthread_join(threads[threadCount],NULL);
			threadCount++;
		}
	}
}
void bagOfThreads(struct row* boolMatrix, struct row* warPath, int numEdges, int numProcess){
	int i, j;
	
	/*Queue will store rows*/
	struct Queue * queue = createQueue(numEdges);
	
	/*mem id*/
	sem_t * sem =  calloc(1, sizeof(sem_t));
	/*Initializing semaphor*/
	sem_init(sem, 1, 0);
	
	// Copies over the original 2D array
    for(i = 0 ; i<numEdges; i++){
		for(j = 0; j < numEdges; j++){
			warPath[i].edgeNums[j] = boolMatrix[i].edgeNums[j];
			enqueue(queue, warPath+i);
		}
	}
			
	ThreadStart(queue, warPath, numProcess, numEdges);
}



