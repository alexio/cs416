#include <ctype.h> 
#include <stdio.h>


int main(int argc, char **argv)
{
    char *projectnumber = argv[1]; //This is the project that we want to run
    char *inputFile = argv[2];
    int projectnum = atoi(projectnumber);
    FILE *indexFile;
    size_t length = 0 ;
    char *temp;
    printf("Project number %d\n",projectnum);
    if (isdigit(projectnum))
    {
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
    }
    printf("Input File: %s\n",inputFile);
    indexFile = fopen(inputFile,"r");
    while(getline(&temp,&length,indexFile) != -1)
    {
        printf("%s",temp);
    }
    return 0;
}
