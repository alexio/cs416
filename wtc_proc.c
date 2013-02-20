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

typedef struct {
	int *row;
} shared_memory;

/*
 * TRANSITIVE-CLOSURE
 */
void warshallsProcessed(struct row* boolMatrix, struct row* warPath, int numEdges, int numProcess) {
	int i, j, k, fork_count, process_count, status;
	pid_t pid, pid_list;
	int memory_id;
    shared_memory *mem_ptr;

    //sem_t *sem;
    // Initializing shared memory
    //sem = mmap(NULL, sizeof(sem_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);

    // Initializing semaphore
    //sem_init(sem, 1, 0);

    memory_id = shmget(IPC_PRIVATE, sizeof(shared_memory), S_IRUSR|S_IWUSR);
    mem_ptr = (shared_memory *)shmat(memory_id,NULL,0);
    mem_ptr->row = calloc(2, sizeof(int));
	mem_ptr->row[0] = 0;
	mem_ptr->row[1] = 0;

    for(i = 0 ; i<numEdges; i++)
		for(j = 0; j < numEdges; j++)
			warPath[i].edgeNums[j] = boolMatrix[i].edgeNums[j];

	// Computation of Warshall’s Transitive Closure
	for (k = 0; k < numEdges; k++) {
		// Forks 'n' number of proccesses
		for (fork_count = 0; fork_count < numProcess; ++fork_count) {
			// Checks if it is the child process
			if ((pid_list = fork()) == 0) {
				for (i = fork_count; i < numEdges; i++) {
					for (j = 0; j < numEdges; j++) {
						//printf("Child %i is doing [%i][%i]\n", fork_count, i, j);
						warPath[i].edgeNums[j] = warPath[i].edgeNums[j] || (warPath[i].edgeNums[k] && warPath[k].edgeNums[j]);
						//printf("Child[%i] @ [%i][%i] = %i\n", fork_count, i, j, warPath[i].edgeNums[j]);
					}
					i++;
				}
				mem_ptr->row[fork_count] = 1;
				printf("%i %i\n", mem_ptr->row[0], mem_ptr->row[1]);
				//printGraph(warPath,numEdges);
				exit(0);
			}
		}
		process_count = numProcess;
		// Wait for the 'n' number of children to finish.
		while (process_count > 0) {
			pid = wait(&status);
			printf("Child with PID %ld exited\n", (long)pid);
			process_count--;
		}
		//printf("At k = %i\n", k);
		//printGraph(warPath,numEdges);
	}

	printf("%i %i\n", mem_ptr->row[0], mem_ptr->row[1]);
	/***
	// Computation of Warshall’s Transitive Closure
	for (k = 0; k < numEdges; k++) {
		// Forks 'n' number of proccesses
		for (fork_count = 0; fork_count < numProcess; fork_count++) {
			// Checks if it is the child process
			if ((pid_list = fork()) == 0) {
				for (i = fork_count; i < numEdges; i++) {
					for (j = 0; j < numEdges; j++) {
						//printf("Child %i is doing [%i][%i]\n", fork_count, i, j);
						warPath[i].edgeNums[j] = warPath[i].edgeNums[j] || (warPath[i].edgeNums[k] && warPath[k].edgeNums[j]);
						printf("Child[%i] @ [%i][%i] = %i\n", fork_count, i, j, warPath[i].edgeNums[j]);
					}
					i++;
				}
				sem_post(sem);
			} else {
				sem_wait(sem);
			}
		}

		// Wait for the 'n' number of children to finish.
		process_count = numProcess;
		while (process_count < numProcess) {
			sem_wait(sem);
			process_count++;
		}
		//printf("At k = %i\n", k);
		//printGraph(warPath,numEdges);
	}
	***/

    //sem_destroy(sem);
    //munmap(sem, sizeof(sem_t));
    return;
}