#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include "operations.h"

// Struct for the shared memory
typedef struct {
	int numEdges;
	int numProcess;
	int *ptr;
	struct row *edge_ptr;
} shared_memory;

// Initializes the rows
struct row createRowPro(int numberOfEdges) {
	int row_id, edge_id;
	struct row *newRow;
	
	row_id = shmget(IPC_PRIVATE, sizeof(struct row*), S_IRUSR|S_IWUSR);
    newRow = (struct row*)shmat(row_id,NULL,0);
    
    edge_id = shmget(IPC_PRIVATE, sizeof(int)*numberOfEdges, S_IRUSR|S_IWUSR);
    newRow->edgeNums = (int *)shmat(edge_id,NULL,0);
	
	return *newRow;
}

// Initializes the array
struct row *createArrayPro(int numOfElements) {
	int i, j, edge_id;
    struct row *array;
    
    edge_id = shmget(IPC_PRIVATE, sizeof(struct row*), S_IRUSR|S_IWUSR);
    array = (struct row*)shmat(edge_id,NULL,0);
    
	for(i = 0; i< numOfElements; i++)
		array[i] = createRowPro(numOfElements);
	
	for(i = 0; i< numOfElements; i++)
		for(j = 0 ; j < numOfElements ; j++)
			array[i].edgeNums[j] = 0;

	//initialize the array to all zero to start with
	printf("First thingy %d\n",array[0].edgeNums[0]);
	return array; 
}

/*
 * CHILD PROCESS CALL
 */
void child_labor(shared_memory *mem_ptr, int fork_count, int k) {
	int rows, columns;
	// Computation of Warshall’s Transitive Closure
	for (rows = fork_count; rows < mem_ptr->numEdges; rows++) { // per row
		for (columns = 0; columns < mem_ptr->numEdges; columns++) { // per column
			mem_ptr->edge_ptr[rows].edgeNums[columns] = mem_ptr->edge_ptr[rows].edgeNums[columns] || (mem_ptr->edge_ptr[rows].edgeNums[k] && mem_ptr->edge_ptr[k].edgeNums[columns]);
			printf("[%i][%i] = %i\n", rows, columns, mem_ptr->edge_ptr[rows].edgeNums[columns]);
		}
		// Child process will loop through every other + (total # process-1) of rows
		rows += mem_ptr->numProcess -1;
	}
	exit(0);
}

// Warshall’s Transitive Closure
void processWarshall(shared_memory *mem_ptr) {
	int process_count, status, fork_count, k;
	// Process IDs
	pid_t pid, pid_list;
	
	for (k = 0; k < mem_ptr->numEdges; k++) {
		// Forks 'n' number of proccesses
		for (fork_count = 0; fork_count < mem_ptr->numProcess; fork_count++) {
			// Checks if it is the child process
			if ((pid_list = fork()) == 0) {
				// Child process does work
				child_labor(mem_ptr, fork_count, k);
			} else {
				// Parent process: taking a chill pill
			}
		}
		process_count = mem_ptr->numProcess;
		// Wait for the 'n' number of children to finish.
		while (process_count > 0) {
			pid = wait(&status);
			process_count--;
		}
	}
}

/*
 * PROCESS
 */
void warshallsProcessed(struct row* boolMatrix, struct row* warPath, int numEdges, int numProcess) {
	int i, j;
	// Memory ID
	int memory_id;
	// Memory Pointer
    shared_memory *mem_ptr;

    sem_t *sem;
    // Initializing shared memory
    sem = mmap(NULL, sizeof(sem_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);

    // Initializing semaphore
    sem_init(sem, 1, 0);

	// Initializes the shared memory and points to it
    memory_id = shmget(IPC_PRIVATE, sizeof(shared_memory), S_IRUSR|S_IWUSR);
    mem_ptr = (shared_memory *)shmat(memory_id,NULL,0);
    mem_ptr->numEdges = numEdges;
    mem_ptr->numProcess = numProcess;
    // Initializes the 2D array and sets everything to 0
    mem_ptr->edge_ptr = createArrayPro(numEdges);

	// Copies over the original 2D array
    for(i = 0 ; i<numEdges; i++)
		for(j = 0; j < numEdges; j++)
			mem_ptr->edge_ptr[i].edgeNums[j] = boolMatrix[i].edgeNums[j];

	processWarshall(mem_ptr);
	
	printf("Final Graph\n");
	printGraph(mem_ptr->edge_ptr,numEdges);
	printf("End\n");

	// Free the shared memory
	shmdt(mem_ptr);
	shmctl(memory_id, IPC_RMID, NULL);
    sem_destroy(sem);
    munmap(sem, sizeof(sem_t));
    return;
}
