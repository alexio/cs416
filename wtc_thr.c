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
	struct Params *input = (struct params*)malloc(sizeof(struct Params));
	
	pthread_t threads[thread_num];
	pthread_attr_t attr; /*thread attrributes*/
	
	for(i = 0 ; i<numOfElements; i++)
	{
		for(j = 0; j < numOfElements; j++)
		{
			warPath[i].edgeNums[j] = boolMatrix[i].edgeNums[j];
		}
	}
	
	int num_rows = numOfElements % thread_num;
	int t_index = 0;
	for(k = 0; k < numOfElements; k++)
	{
		for(i = 0 ; i < numOfElements ; i++)
		{ /* going to iterate through thread input params variable and store a number of elements equal to num_threads before creating thread*/
			/*or each thread takes a row at a time*/
				input->i = i;
				input->k = k;
				input->element = warPath[i];
				input->numOfElements = numOfElements;
				if(t_index > thread_num){
					t_index = 0;
				}
				/*implement the max number of threads that can be operating at a given time*/
				pthread_create(&threads[t_index], NULL, bagIt, input);
				t_index++;
		}
	}
}


void bagIt(void* param){
				
	struct Params * input = (struct Params *)param;
	
	for(j = 0; j < input->numOfElements; j++){
		
		input->element[input->i][j]= input->element[input->i][j] || (input->element[input->i][input->k] && input->element[input->k][j]);
	}
}
