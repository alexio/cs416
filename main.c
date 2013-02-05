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
    node *nodeone;
    node *nodetwo;
    printf("Project number %d\n",projectnum);
    //if (isdigit(projectnum))
    /*{
        if (projectnum == 1)
        {
            printf("Project 1");
        }

        if (projectnum == 2)
        {
            printf("Project 2");
        }

        if (projectnum == 3)
        {
            printf("Project 3");
        }

        if (projectnum == 4)
        {
            printf("Project 4");
        }
    }*/
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
            nodeone = createNode(strtok(NULL," "));
            //creating an edge
            printf("Edge = %s",temp);
        }
        count++;
    }
    fclose(indexFile);
    return 0;
}
