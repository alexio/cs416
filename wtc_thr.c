#include <stdio.h>
#include <stdlib.h>
#include "operations.h"
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void warshalls(struct row* boolMatrix, struct row* warPath, int numOfElements, int thread_num)
{
	int i, j, k;
	struct Params *input = (struct params*)malloc(sizeof(struct Params));
	
	input->numOfElements = numOfElements;
	
	pthread_t threads[thread_num];
	pthread_attr_t attr; /*thread attrributes*/
	
	for(i = 0 ; i<numOfElements; i++)
	{
		for(j = 0; j < numOfElements; j++)
		{
			warPath[i].edgeNums[j] = boolMatrix[i].edgeNums[j];
		}
	}
	
	int num_rows = numOfElements / thread_num;
	int remainder = numOfElements % thread_num;
	
	input->i = (int *)malloc(sizeof(int)*num_rows);
	input->k = (int *)malloc(sizeof(int)*num_rows);
	input->element = (int *)malloc(sizeof(struct row)*num_rows);
	
	int t_index = 0;
	int row_counter = 0;
	for(k = 0; k < numOfElements; k++)
	{
		for(i = 0 ; i < numOfElements ; i++)
		{ /* going to iterate through thread input params variable and store a number of elements equal to num_threads before creating thread*/
			/*or each thread takes a row at a time*/
				input->i[row_counter] = i;
				input->k[row_counter] = k;
				input->element[row_counter] = warPath[i];
				row_counter++;
				
				if(row_counter == num_rows &&){/*wait until Param object has all the rows for the thread*/
	
					/*implement the max number of threads that can be operating at a given time*/
					pthread_create(&threads[t_index], NULL, bagIt, input);
					t_index++;
					row_counter = 0;
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
