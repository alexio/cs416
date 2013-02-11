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
    struct adjLL *storage;
    struct  node *nodeone;
    struct node *nodetwo;
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
            printf("Number of edges = %s",temp);
        }
        else
        {
            //creating a node
            nodeone = createNode(strtok(temp," "));
	    if(count == 2)
	    {
		storage = createAdjLL(nodeone);
	    }
	    if(alreadyInList(storage,nodeone) == 0)
	    {
            	nodeone = createNode(strtok(NULL," "));
	    }
            //add a node to the node list if its not already there
            //check to see if its there or not
	    if (alreadyInList(storage,nodetwo) == 0)
	    {
	    	addNodeToList(storage,nodetwo);
            }
	    //make an edgebetween nodeone and nodetwo
	    createEdge(nodeone,nodetwo);
            printf("Edge = %s",temp);
        }
        count++;
    }
    fclose(indexFile);
    return 0;
}
