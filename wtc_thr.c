#include <stdio.h>
#include <stdlib.h>
#include "operations.h"
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *bagIt(void* param){
			
	printf("Thread\n");	
	struct Params *input = (struct Params *)param;

	int t, j;
	for(t = 0; t < input->numOfRows; t++){
		printf("Getting into outter\n");
		for(j = 0; j < input->numOfElements; j++){
			
			input->element[t].edgeNums[j] = input->element[t].edgeNums[j] || (input->element[t].edgeNums[input->k] && input->element[input->k].edgeNums[j]);
			printf("Getting in the for loop inner\n");
			//input->element[t].edgeNums[j] = 1;
		}
	}
	return NULL;
}

void warshallsThreaded(struct row* boolMatrix, struct row* warPath, int numOfElements, int thread_num)
{
	int i, j, k;
	struct Params*input;// = (struct Params*)calloc(1, sizeof(struct Params)); /*must allocate one at a time */
	/*if(input != NULL)
	{	
		fprintf(stderr,"ERROR: out of memory \n");
		return;
	}*/
	char check = 'n';/*What is this variable?*/
	
	//input->numOfElements = numOfElements;
	
	pthread_t threads[thread_num];
	
	/*pthread_attr_t attr; /thread attrributes*/
	
	/*copy over the array*/
	for(i = 0 ; i<numOfElements; i++)
	{
		for(j = 0; j < numOfElements; j++)
		{
			warPath[i].edgeNums[j] = boolMatrix[i].edgeNums[j];
		}
	}
	
	int num_rows = numOfElements / thread_num;
	int remains = numOfElements % thread_num;

	if(remains != 0){
		check = 'y';
		thread_num--;
	}
	
	//input->i = malloc(sizeof(int)*num_rows); /*int array*/
	//input->element = malloc(sizeof(struct row)*(num_rows+1));
	
	int t_index = 0;
	int row_counter = 0;
	printf("Number of rows %d\n",num_rows);
	for(k = 0; k < numOfElements; k++)
	{
		input->element[k] = warPath[k]; /* Does this change the row? */
		for(i = 0 ; i < numOfElements ; i++)
		{ /* going to iterate through thread input params variable and store a number of elements equal to num_threads before creating thread*/
			/*or each thread takes a row at a time*/
				input = (struct Params*)calloc(1, sizeof(struct Params));
				if(input != NULL)
				{	
					fprintf(stderr,"ERROR: out of memory \n");
					exit(1);
				}
				input->i = malloc(sizeof(int)*num_rows); /*int array*/
				input->element = malloc(sizeof(struct row)*(num_rows+1));
				input->i[row_counter] = i;
				input->numOfElements = numOfElements;
				input->k = k;
				input->element[row_counter++] = warPath[i];
				
				if(check == 'y' && t_index == thread_num && (i == (numOfElements - 1))){
 					input->numOfRows = row_counter;
					/*implement the max number of threads that can be operating at a given time*/
					printf("Creating a thread\n");
					pthread_create(&threads[t_index], NULL, (void *)&bagIt, (void *) &input);
					t_index++;
				}
				else if(row_counter == (num_rows+1) && t_index < thread_num){/*wait until Param object has all the rows for the thread*/
					/*printGraph(input->element, 2);*/
					input->numOfRows = row_counter;
					/*implement the max number of threads that can be operating at a given time*/
					pthread_create(&threads[t_index], NULL, bagIt, input);
					t_index++;
				}
		}
	}
	for(i = 0 ; i < thread_num ; i++)
	{
		pthread_join(threads[i],NULL);
	}
}
