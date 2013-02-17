#include <stdio.h>
#include <stdlib.h>
#include "operations.h"
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void bagOfTask(struct row* boolMatrix, struct row* warPath, int numOfElements)
{
	int i, j, k;
	struct Queue *tempQ = createQueue(numOfElements);
	struct Params *input = (struct params*)malloc(sizeof(struct Params));
	
	for(i = 0 ; i<numOfElements; i++)
	{
		for(j = 0; j < numOfElements; j++)
		{
			warPath[i].edgeNums[j] = boolMatrix[i].edgeNums[j];
		}
		enqueue(i);
	}
	for(k = 0; k < numOfElements; k++)
	{
		for(i = 0 ; i < numOfElements ; i++)
		{
			while(tempQ->size > 0){
				input->i = i;
				input->k = k;
				input->element = dequ
				pthread_create(&tid, NULL, bagIt, warPath);
			}
		}
	}
}


void bagIt(void* param){
				
	for(j = 0; j < numOfElements; j++){
		a[i][j]=a[i][j]||(a[i][k] && a[k][j]);
	}
	temp->size--;
}
