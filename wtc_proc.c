#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include "operations.h"

void warshalls(struct row* boolMatrix, struct row* warPath, int numEdges, int numProcess) {

	pid_t pid[numProcess];
	sem_t *sharedMem;
	int i;

	/* Shared memory */
	sharedMem = mmap(NULL, sizeof(sem_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, -0);
	/* Initializing a shared binary semaphore */
	sem_init(sem, 1, 0);

	/* Initializing each process */
	for (i = 0; i < numProcess; i++) {
		if (pid[i] == 0) {
			// child labor starts here

			sem_post(sem);
		} else {
			sem_wait(sem);

			// parent starts here
		}
	}

	sem_destory(sem);
	munmap(sem, sizeof(sem_t));
	return 0;
}