#ifndef OPERATIONS_H_
#define OPERATIONS_H_

int **createArray(int numOfElements);

void printGraph(int **graph, int numberOfElements);

void warshalls(int **boolMatrix, int **warPath, int numberOfElements);

void bagOfTask(int **boolMatrix, int **warPath, int numberOfElements);

#endif
