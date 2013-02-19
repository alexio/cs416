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


int * sharedMemory(struct *row sharedRowArray)
{
	int seg_id;
	int seg_size;
	struct shmid_ds shmbuffer;
	int *k;
	seg_id = shmget(IPC_PRIVATE, seg_size, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	sharedRowArray = (struct row *) shmat(seg_id, NULL ,0);
	k = (struct row *) shmat(seg_id, NULL ,0);
	return k;
}



void warshallsProcessed(struct row* boolMatrix, struct row* warPath, int numEdges, int numProcess) {

	pid_t pid[numProcess];
		sem_t *sharedMem;
	sem_t kLock;
	int i;
		int until;
	int j,q,z;
	struct row * sharedRow;
	int offSetValue; //The number of rows each thread will be assigned to
	int leftOver; //If the number of threads / number of rows is not even (remainder) then the last thread will have less threads than the ones before it
	int k = 0 ;
	int *ktmp;
	int temp;
	/* Shared memory */
	sharedMem = mmap(NULL, sizeof(sem_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, -0);
	sharedRow = mmap(NULL, sizeof(struct row), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, -0);
	ktmp = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, -0);
	/* Initializing a shared binary semaphore */
	sem_init(sharedMem, 1, 0);
	sem_init(&kLock,1,0);	
	offSetValue = numEdges/ numProcess;
	leftOver = numEdges % numProcess;
	/* Initializing each process */
		for (k = 0; k < numEdges; k++) 
		{
			
			ktmp = k;
			//Lock k so that it cannot be incremented
			for (i = 0 ; i <= numEdges;)
			{	
				if (fork() == 0) 
				{
					printf("Process created \n");
					// child labor starts here; lets start making nikes
					temp = offSetValue+i;
					printf("Offset value: %d \n",temp);
						while(i < temp)
						{
						//	printf("Process created \n");
							k = &ktmp
							for(j = 0 ; j < numEdges ; j++)
							{
								warPath[i].edgeNums[j] = warPath[i].edgeNums[j] || (warPath[i].edgeNums[k] && warPath[k].edgeNums[j]);
							}
							i++; //increment the row that the process works on
						}
						sem_post(sharedMem);
						while(1) // wait for the all processes to return
						{
							if (sem_getvalue(sharedMem,0) == numProcess)
							{
								break;
							}
						 }
					//we need to wait for all processes to finish and increment the k value then loop again
					exit(0);
				}
				i+=offSetValue;
			}
			while(1) // wait for the all processes to return
			{
				if (sem_getvalue(sharedMem,0) == numProcess)
				{
					break;
				}
			}
		ktmp = k;
		printf("K is now %d\n");
		}
	while(1)
	{	
		sem_wait(sharedMem);
		printf("Waiting\n");
		if (sem_getvalue(sharedMem,0) == 0)
		{
			break;
		}
	}
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
