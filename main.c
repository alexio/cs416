#include <ctype.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"

int main(int argc, char **argv)
{
	char *projectnumber = argv[1]; //This is the project that we want to run
	char *inputFile = argv[2];
	int projectnum = atoi(projectnumber);
	FILE *indexFile;
	size_t length = 0 ;
	char *temp;
	int count = 0;
	//struct adjLL *storage;
	//struct node *nodeone;
	//struct node *nodetwo;
	int **twoDArray;
	int **warPath;
	int numberOfEdges = 0;
	int temp3 = 0;
	int temp4 = 0 ;
	int i = 0 ;
	//int j = 0 ;
	//int currentIndex = 0 ;
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
		}
		else if (count == 1)
		{
			//Create a 2d array to store the edges and verticies
			printf("Number of edges = %s",temp);
			numberOfEdges = atoi(temp);
			printf("Making the array \n");
			twoDArray = createArray(numberOfEdges);
			warPath = createArray(numberOfEdges);
			printf("Done making the array %d %d\n",i,numberOfEdges);
		}
		else
		{
			char *token = strtok(temp," ");
			temp3 = atoi(token);
			printf("Got the first edge %d\n",temp3);
			//free(token);
			//tokenize and then turn into int
			token = strtok(NULL," ");
			temp4 = atoi(token);
			printf("Got the second edge %d\n",temp4);
			//add the edge to the graph
		//	printf("adding");
			twoDArray[temp3][temp4] = 1;
			twoDArray[temp4][temp3] = 1;
		}
		count++;
	}
	fclose(indexFile);
	printf("Printing the graph\n");
	//int i;
	//int j;
	printGraph(twoDArray,numberOfEdges);
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
	printf("Warshalls\n");
	warshalls(twoDArray,warPath,numberOfEdges);
	printGraph(warPath,numberOfEdges);
	//Bag of Tasks
	bagOfTask(twoDArray,warPath,numberOfEdges);
	return 0;
}
