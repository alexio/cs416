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
	struct node *nodeone;
	struct node *nodetwo;
	int **twoDArray;
	int numberOfEdges = 0;
	int temp3 = 0;
	int temp4 = 0 ;
	int i = 0 ;
	int j = 0 ;
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
			printf("adding");
			twoDArray[temp3][temp4] = 1;
			twoDArray[temp4][temp3] = 1;
			printf("adding2");
			/*if(twoDArray[temp3][0] == '\0')
			{
				nodeone = createNode(temp3);
				addNodeToList(twoDArray,nodeone,temp3);
			}
			else //set variable if it already exists
			{
				*nodeone = twoDArray[temp3][0];
			}
			temp3 = atoi(strtok(NULL," "));
			//create second node if it doesnt exist already
			if (twoDArray[temp3][0] != 1)
			{
				//Add the second node to the array
				twoDArray[temp3][0] = 1;
				//nodetwo = createNode(temp3);
				//addNodeToList(twoDArray,nodeone,temp3);
			}
			else //set variable if it already exists
			{
				nodetwo = twoDArray[temp3][0];
			}*/
			//make the edge for the two nodes
			//printf("Adding edge %s\n",temp);
		}
		count++;
	}
	fclose(indexFile);
	printf("Printing the graph\n");
	//int i;
	//int j;
	for(i = 0; i <numberOfEdges-1 ; i++)
	{
		for(j = 0 ; j < numberOfEdges-1 ; i++)
		{
			printf("%d",twoDArray[i][j]);
		}
		printf("\n");
	}
	return 0;
}
