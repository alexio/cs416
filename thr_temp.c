#include <stdio.h>
#include <stdlib.h>
#include "operations.h"
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

/*void *bagIt(void* param){
			
	printf("Thread\n");	
	struct Params *input = (struct Params *)param;

	int t, j;
	for(t = 1; t < input->numOfRows; t++){
		for(j = 0; j < input->numOfElements; j++){
			
<<<<<<< HEAD
			input->element[t].edgeNums[j] = input->element[t].edgeNums[j] || (input->element[t].edgeNums[input->k] && input->element[input->k].edgeNums[j]);
			printf("after %d %d\n", j,t);
=======
			input->element[t].edgeNums[j]= input->element[t].edgeNums[j] || (input->element[t].edgeNums[input->k] && input->element[0].edgeNums[j]);
			
			input->element[t].edgeNums[j] = 1;
>>>>>>> 83453b47fb34f1b53fe585ea833d5414859253f3
		}
	}
	return NULL;
}

void warshallsThreadedFirst(struct row* boolMatrix, struct row* warPath, int numOfElements, int thread_num)
{
	int i, j, k, t;
	struct Params* input; /*must allocate one at a time */
	if((input = (struct Params*)calloc(thread_num+1, sizeof(struct Params))) == 0)
	{	
		fprintf(stderr,"ERROR: out of memory \n");
		return;
	}
	char check = 'n';/*Check to see if numOfElements is evenly divided by numOfThreads, if it's not this 
	lets you know if there is a remainder and allows you to enact a special case*/
	
	pthread_t threads[thread_num];
<<<<<<< HEAD
	/*copy over the array*/
=======
	
	pthread_attr_t attr; /thread attrributes
	//copy over the array
>>>>>>> 83453b47fb34f1b53fe585ea833d5414859253f3
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

	int t_index = 0; /*implement the max number of threads that can be operating at a given time*/
	
	for(t = 0; t < thread_num;t++){
		if((input[t].element = malloc(sizeof(struct row)*(num_rows+1))) == 0){ /*contains array of rows to pass into threads*/
			fprintf(stderr,"ERROR: out of memory \n");
			return;
		}
	}
	int row_counter = 0;
	for(k = 0; k < numOfElements; k++)
	{
		
		input[t_index].element[row_counter++] = warPath[k]; /* Does this change the row? */
		input[t_index+1].element[row_counter-1] = warPath[k]; /* Does this change the row? */
		for(i = 0 ; i < numOfElements ; i++)
<<<<<<< HEAD
		{ /* going to iterate through thread input params variable and store a number of elements equal to num_threads before creating thread*/
			/*or each thread takes a row at a time*/ 
				input[t_index].numOfElements = numOfElements;
				input[t_index].element[row_counter++] = warPath[i];
				input[t_index].k = k;
				if(check == 'y' && (i == (numOfElements - 1))){	
 					input[t_index].numOfRows = row_counter;
 					printf("Getting rows %d\n",t_index);
					pthread_create(&threads[t_index], NULL, (void *)&bagIt, (void *)&input[t_index]);
=======
		{  going to iterate through thread input params variable and store a number of elements equal to num_threads before creating thread
			or each thread takes a row at a time
				input->i[row_counter] = i;
				input->k = k;
				input->element[row_counter++] = warPath[i];
				
				if(check == 'y' && t_index == thread_num && (i == (numOfElements - 1))){
 					input->numOfRows = row_counter;
					implement the max number of threads that can be operating at a given time
					pthread_create(&threads[t_index], NULL, (void *)&bagIt, (void *) &input);
>>>>>>> 83453b47fb34f1b53fe585ea833d5414859253f3
					t_index++;
				}
<<<<<<< HEAD
				else if(row_counter == (num_rows+1) && t_index < thread_num){/*wait until Param object has all the rows for the thread*/
					printf("Thread going %d\n", k);
					printf("Getting rows %d\n",t_index);
					input[t_index].numOfRows = row_counter;
					pthread_create(&threads[t_index], NULL, bagIt, (void*)&input[t_index]);
					t_index++;
					row_counter = 1;
				}
		}
		/*wait for threads*/
		for(t = 0 ; t < thread_num ; t++)
		{
			pthread_join(threads[t],NULL);
		}
		
		/*free mem*/
		for(t = 0; t < thread_num; t++){
			free(input[t].element);
		}
		free(input);
		
		/*remalloc*/
		if((input = (struct Params*)calloc(thread_num, sizeof(struct Params))) == 0){
			fprintf(stderr,"ERROR: out of memory \n");
			return;
		}
		
		for(t = 0; t < thread_num;t++){
			if((input[t].element = malloc(sizeof(struct row)*(num_rows+1))) == 0){
				fprintf(stderr,"ERROR: out of memory \n");
				return;
			}
		}
		t_index = 0;
		row_counter = 0;
	}	
}
=======
				else if(row_counter == (num_rows+1) && t_index < thread_num){//wait until Param object has all the rows for the thread
					//printGraph(input->element, 2);
					//input->numOfRows = row_counter;
					//implement the max number of threads that can be operating at a given time
					//pthread_create(&threads[t_index], NULL, bagIt, input);
					//t_index++;
					//row_counter = 1;
				}
		}
//		row_counter = 0;
		for(i = 0 ; i < thread_num ; i++)
		{
			pthread_join(&threads[i],NULL);
		}*/
/*	}
	for(i = 0 ; i < thread_num ; i++)
	{
		pthread_join(threads[i],NULL);
	}
}*/
>>>>>>> 83453b47fb34f1b53fe585ea833d5414859253f3
