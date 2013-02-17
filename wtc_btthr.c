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


void bagIt(void* param){
				
	struct Params * input = (struct Params *)param;
	
	for(j = 0; j < input->numOfElements; j++){
		
		input->element[input->i][j]= input->element[input->i][j] || (input->element[input->i][input->k] && input->element[input->k][j]);
	}
}
