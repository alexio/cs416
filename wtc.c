#include <ctype.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "operations.h"
#include <semaphore.h>


#define maxline 250

int main(int argc, char **argv)
{
	struct timeval time_start, time_end;
	gettimeofday(&time_start, NULL);

	if (argc < 3) {
		printf("ERROR: Insufficient Inputs!\n");
		return 0;
	}
	char *projectnumber = argv[1]; //This is the project that we want to run
	char *inputFile = argv[2];
	int projectnum = atoi(projectnumber);
	FILE *indexFile;
	size_t length = 0 ;
	char *temp = calloc(maxline, sizeof(char));
	int count = 0;
	int numberOfThreads = 0;
	
	struct row *twoDArray;
	struct row *warPath;
	int numberOfEdges = 0;
	int temp3 = 0;
	int temp4 = 0 ;
	
	printf("Project number %d\n",projectnum);
	printf("Input File: %s\n",inputFile);
	indexFile = fopen(inputFile,"r");
	if (indexFile == NULL)
	{
		printf("ERROR: Invalid filename \n");
		return 0;
	}
	
	while(getline(&temp,&length,indexFile) != -1)
	{
		if (count == 0)
		{
			printf("Threads or Processes = %s",temp);
			numberOfThreads = atoi(temp);
		}
		else if (count == 1)
		{
			/*Create a 2d array to store the edges and verticies*/
			printf("Number of edges = %s",temp);
			numberOfEdges = atoi(temp);
			printf("Making the array \n");
			twoDArray = createArray(numberOfEdges);
			warPath = createArray(numberOfEdges);
			printf("Done making the array %d\n",numberOfEdges);
		}
		else
		{
			printf("Else :%d\n", count);
			char *token = strtok(temp," ");
			temp3 = atoi(token);
			printf("Temp3 :%d\n", temp3);
			/*printf("Got the first edge %d\n",temp3);
			free(token);
			tokenize and then turn into int*/
			token = strtok(NULL," ");
			temp4 = atoi(token);
			printf("Temp4 end :%d\n", temp4);
			/*printf("Got the second edge %d\n",temp4);
			add the edge to the graph
			printf("adding");*/
			twoDArray[temp3-1].edgeNums[temp4-1] = 1;
		}
		count++;
	}
	printf("close file\n");
	fclose(indexFile);
	printf("Printing the graph\n");
	//int i;
	//int j;
	//printGraph(twoDArray,numberOfEdges);
	/*for(i = 0; i <numberOfEdges ; i++)
	{
		//printf("i is %d\n",i);
		for(j = 0 ; j < numberOfEdges ; j++)
		{
		//	printf("j is %d\n",j);
			printf("%d",twoDArray[i][j]);
		}
		printf("\n");
	}*/
	//Warshaws Algorithum
	if(projectnum == 1)
	{
		printf("Warshalls Transitive Closure - Process\n");
		warshallsProcessed(twoDArray,warPath,numberOfEdges,numberOfThreads);
		//printGraph(warPath,numberOfEdges);
	}
	else if(projectnum == 2)
	{
		printf("Warshalls Transitive Closure - Threads\n");
		warshallsThreaded(twoDArray,warPath,numberOfEdges,numberOfThreads);
		//printGraph(warPath,numberOfEdges);
		
	}
	else if (projectnum == 3)
	{
		printf("Bag of Tasks - Process\n");
		//bagOfTask(twoDArray,warPath,numberOfEdges);
		printGraph(warPath,numberOfEdges);
	}
	else if (projectnum == 4)
	{
		printf("Bag of Tasks - Threads\n");
		//bagOfTask(twoDArray,warPath,numberOfEdges);
		printGraph(warPath,numberOfEdges);
	}
	freeAll(twoDArray,warPath,numberOfEdges);
	/*printf("Warshalls\n");
	warshalls(twoDArray,warPath,numberOfEdges);
	printGraph(warPath,numberOfEdges);
	//Bag of Tasks
	bagOfTask(twoDArray,warPath,numberOfEdges);*/

	gettimeofday(&time_end, NULL);
	printf("Time: %ld us\n", ((time_end.tv_sec * 1000000 + time_end.tv_usec)
		  - (time_start.tv_sec * 1000000 + time_start.tv_usec)));
	return 0;
}
