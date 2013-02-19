#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include "operations.h"

void warshallsProcessed(struct row* boolMatrix, struct row* warPath, int numEdges, int numProcess) {
	
		pid_t pid[numProcess];
		sem_t *sharedMem;
		sem_t kLock;
		int i;
		int until;
		int j,q;
		int offSetValue; //The number of rows each thread will be assigned to
	int leftOver; //If the number of threads / number of rows is not even (remainder) then the last thread will have less threads than the ones before it
	int k;
		/* Shared memory */
		sharedMem = mmap(NULL, sizeof(sem_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, -0);
		/* Initializing a shared binary semaphore */
		sem_init(sharedMem, 1, 0);
		sem_init(&kLock,1,0);

	offSetValue = numEdges/ numProcess;
	leftOver = numEdges % numProcess;
	
		/* Initializing each process */
		for (k = 0; k < numProcess; k++) {
			for (i = 0 ; i<numProcess ; i++)
			{	
				pid[i] = fork();
				if (pid[i] == 0) {
					// child labor starts here; lets start making nikes
					 printf("Process created \n");
					until = j+offSetValue;
					while(j != until)
					{
						for(q = 0 ; q < numEdges ; q++)
						{
							warPath[j].edgeNums[q] = warPath[j].edgeNums[q] || (warPath[j].edgeNums[i] && warPath[i].edgeNums[q]);
						}
						j++;//j will go until the upperbound is reached
					}
					sem_post(sharedMem);
					exit(0);
				} else {
					sem_wait(sharedMem);
					// parent starts here
				}
			}}
	
		//sem_destory(sem);
		munmap(sharedMem, sizeof(sem_t));
		return 0;
}

/*void warshalls(struct row* boolMatrix, struct row* warPath, int numEdges, int numProcess) {

	int i;
	int j;
	int q;
	//int threadID = 0 ;
	//pid_t pid;
	int pid;
	int offSetValue;
	int leftOver;
	//int count = 0;
	sem_t sem;
	int current; //current position in the graph
	char * mapedSem;
	char * mapedArray;
	mapedSem = mmap(NULL, sizeof(sem_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, -0);
	mapedArray = mmap(NULL, sizeof(struct row *), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, -0);

	sem_init(&sem,1,0);

	for(i = 0 ; i < numOfElements; i++)
	{
		for(j = 0 ; j < numOfElements ; j++)
		{
		:q
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
		for(j = 0 ; j < numOfElements ; j++)//row number
		{	
			if((pid = fork()) == 0)
			{
				printf("Process created \n");
				until = j+offSetValue;
				while(j != until)
				{
					for(q = 0 ; q < numOfElements ; q++)
					{
						warPath[j].edgeNums[q] = warPath[j].edgeNums[q] || (warPath[j].edgeNums[i] && warPath[i].edgeNums[q]);
					}
					j++;//j will go until the upperbound is reached
				}
				sem_post(&sem);
				printf("Posting to semaphore \n");
				exit(0);
			}
			j = j+offSetValue;
		}
		i+=offSetValue;
	}
	q = 0;
	printf("number of threads \n%d",numberOfThreads);
	while(q < numberOfThreads) //wait for all the threads to finish
	{
		printf("\nwaiting\n");
		sem_wait(&sem);
		q++;
		printf("q is %d\n",q); 
	}
}*/
