#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include "operations.h"
#include <sys/shm.h>
#include <sys/stat.h>

/*
 * TRANSITIVE-CLOSURE
 */
void warshallsProcessed(struct row* boolMatrix, struct row* warPath, int numEdges, int numProcess) {
	int i, j, k, fork_count, process_count, status;
	pid_t pid, pid_list[numProcess];
    

    sem_t *sem;
    // Initializing shared memory
    sem = mmap(NULL, sizeof(sem_t), PROT_READ|PROT_WRITE, MAP_SHARED, -1, 0);

    // Initializing semaphore
    sem_init(sem, 1, 0 );

    /***
	// Computation of Warshall’s Transitive Closure
	for (k = 0; k < numEdges; k++) {
		// Forks 'n' number of proccesses
		for (fork_count = 0; fork_count < numProcess; ++fork_count) {
			// Checks if it is the child process
			if ((pid = fork()) == 0) {
				printf("Child %i at k = %i\n", fork_count, k);
				for (i = 0; i < numEdges; i++) {
					for (j = 0; j < numEdges; j++) {
						//printf("Child %i is doing %i\n", fork_count, j);
						warPath[i].edgeNums[j] = warPath[i].edgeNums[j] || (warPath[i].edgeNums[k] && warPath[k].edgeNums[j]);
					}
				}
				sem_post(sem);
				exit(0);
			}
		}
		
		process_count = numProcess;
		// Wait for the 'n' number of children to finish.
		while (process_count > 0) {
			sem_wait(sem);
			printf("Wait at k = %i\n", k);
			--process_count;
		}
	}
	***/

	// Computation of Warshall’s Transitive Closure
	for (k = 0; k < numEdges; k++) {
		// Forks 'n' number of proccesses
		for (fork_count = 0; fork_count < numProcess; ++fork_count) {
			// Checks if it is the child process
			if ((pid_list[fork_count] = fork()) == 0) {
				printf("========\n");
				printf("Child %i\n", fork_count);
				printf("========\n");
				for (i = 0; i < numEdges; i++) {
					for (j = 0; j < numEdges; j++) {
						//printf("Child %i is doing [%i][%i]\n", fork_count, i, j);
						warPath[i].edgeNums[j] = warPath[i].edgeNums[j] || (warPath[i].edgeNums[k] && warPath[k].edgeNums[j]);
						printf("[%i]", warPath[i].edgeNums[j]);
					}
					printf("\n");
				}
				sem_post(sem);
				exit(0);
			}
		}
		process_count = numProcess;
		// Wait for the 'n' number of children to finish.
		while (process_count > 0) {
			pid = wait(&status);
			printf("Child with PID %ld exited\n", (long)pid);
			--process_count;
		}
	}

    sem_destroy(sem);
    munmap(sem, sizeof(sem_t));
    return;
}