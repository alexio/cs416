#include <ctype.h> 
#include <stdio.h>
#include "main.h"

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
	struct  node *nodeone;
	struct node *nodetwo;
	struct node **twoDArray;
	int numberOfEdges = 0;
	int temp3 = 0;
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
			twoDArray = createArray(numberOfEdges);
		}
		else
		{
			temp3 = atoi(strtok(temp," "));
			//creating the fist node if it doesnt exist already
			if(twoDArray[temp3][0] == NULL)
			{
				nodeone = createNode(temp3);
				addNodeToList(twoDArray,nodeone,temp3);
			}
			else //set variable if it already exists
			{
				nodeone = twoDArray[temp3][0];
			}
			temp3 = atoi(strtok(NULL," "));
			//create second node if it doesnt exist already
			if (twoDArray[temp3][0] == NULL)
			{
				nodetwo = createNode(temp3);
				addNodeToList(twoDArray,nodeone,temp3);
			}
			else //set variable if it already exists
			{
				nodetwo = twoDArray[temp3][0];
			}
			createEdge(nodeone,nodetwo);
			printf("Adding edge %s\n",temp);
		}
		count++;
	}
	fclose(indexFile);
	return 0;
}
