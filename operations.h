#ifndef OPERATIONS_H_
#define OPERATIONS_H_

int **createArray(int numOfElements);

void printGraph(int **graph, int numberOfElements);

void warshalls(int **boolMatrix, int **warPath, int numberOfElements);

void bagOfTask(int **boolMatrix, int **warPath, int numberOfElements);

struct Queue
{
	int cap;
	int size;
	int head;
	int tail;
	int * elements;
};

struct Queue * createQueue(int elementsMax);
void destroyQueue(struct Queue *removed);
void dequeue(struct Queue *queue);
void enqueue(struct Queue *queue, int adding);
void freeAll(int **boolMatrix, int **warPath, int size);
#endif
