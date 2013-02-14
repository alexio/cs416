#include <stdio.h>
#include <stdlib.h>
#include "operations.h"
#include <math.h>
#include <string.h>
#include <malloc.h>


int **createArray(int numOfElements) {
	int i = 0;
	int j;
//	int array[numOfElements][numOfElements] = { {0 } };
	int **array = (int **) malloc(numOfElements*(sizeof(int *)));
	for(i = 0; i< numOfElements; i++)
	{
		//for(j = 0 ; j < numOfElements ; j++)
		//{
			array[i] = (int *) calloc(numOfElements,(sizeof(int)));
		//}	 
	}
	for(i = 0; i< numOfElements; i++)
	{
		//printf("i is: %d\n",i);
		for(j = 0 ; j < numOfElements ; j++)
		{
			array[i][j] = 0;
		}	 
	}

	//initialize the array to all zero to start with
	printf("First thingy %d",array[0][0]);
	return array; 
}

void warshalls(int **boolMatrix, int **warPath, int numOfElements)
{
	int i;
	int j;
	int q;

	for(i = 0 ; i < numOfElements; i++)
	{
		for(j = 0 ; j < numOfElements ; j++)
		{
			//Copy over the matrix to the path
			warPath[i][j] = boolMatrix[i][j];
		}
	}

	for(i = 0 ; i < numOfElements; i++)
	{
		for(j = 0 ; j < numOfElements ; j++)
		{
			if (warPath[i][j] == 1)
			{
				for(q = 0 ; q < numOfElements ; q++)
				{
					if (warPath[j][q] == 1)
					{
						warPath[i][q] = 1;
					}
				}
			}
		}
	}
}


void printGraph(int **graph, int numOfElements)
{
	int i;
	int j;
	for(i = 0 ; i < numOfElements; i++)
	{
		for(j = 0 ; j < numOfElements ; j++)
		{
			printf("%d",graph[i][j]);
		}
		printf("\n");
	}
}



void bagOfTask(int **boolMatrix, int **warPath, int numOfElements)
{


}
