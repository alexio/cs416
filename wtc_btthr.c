#include <stdio.h>
#include <stdlib.h>
#include "operations.h"
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void *child_laborThread_bt(void *param) {
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


// Warshall’s Transitive Closure Threads
void threadedWarshall_bt(struct row *warPath,int threadnum,int numEdges) {
	struct Params *attr = (struct Params *)calloc(1,sizeof(struct Params));
	attr->edge_ptr = (struct row*)calloc(numEdges,sizeof(struct row));
	// Thread IDs
	int threadCount,k = 0;
	pthread_t threads[threadnum];
	
	for (k = 0; k < numEdges; k++) {
		// Forks 'n' number of proccesses
		for (threadCount = 0; threadCount < threadnum; threadCount++) {
			// Checks if it is the child process
			attr->k = k;
			attr->thread_num = threadCount;
			attr->numEdges = numEdges;
			attr->edge_ptr = warPath;
			printf("Launching threads \n");
			pthread_create(&threads[threadCount],NULL,child_laborThread_bt,attr);
		}
		threadCount = 0;
		// Wait for the 'n' number of children to finish.
		while (threadCount < threadnum) {
			pthread_join(threads[threadCount],NULL);
			threadCount++;
		}
	}
}

void bagOfThreads_bt(struct row* boolMatrix, struct row* warPath, int numEdges, int numProcess) {
	int i, j;
	// Memory ID
    sem_t *sem = calloc(1,sizeof(sem_t)); 
    // Initializing semaphore
    sem_init(sem, 1, 0);

	// Initializes the shared memory and points to it

	// Copies over the original 2D array
    for(i = 0 ; i<numEdges; i++)
		for(j = 0; j < numEdges; j++)
			warPath[i].edgeNums[j] = boolMatrix[i].edgeNums[j];

	//processWarshall(mem_ptr);
	//printf("Done with creation \n");
	threadedWarshall_bt(warPath,numProcess,numEdges);
	printf("Final Graph\n");
	printGraph(warPath,numEdges);
	printf("End\n");

	// Free the shared memory
	//shmdt(mem_ptr);
	//shmctl(memory_id, IPC_RMID, NULL);
    //sem_destroy(sem);
    //munmap(sem, sizeof(sem_t));
    return;
}
