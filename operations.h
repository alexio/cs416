#ifndef OPERATIONS_H_
#define OPERATIONS_H_

int **createArray(int numOfElements);

void printGraph(int **graph, int numberOfElements);

void warshalls(int **boolMatrix, int **warPath, int numberOfElements);

void bagOfTask(int **boolMatrix, int **warPath, int numberOfElements);

typedef struct Queue
{
	int cap;
	int size;
	int head;
	int tail;
	int * elements;
}

Queue * createQueue(int elementsMax);
void destroyQueue(Queue *removed);
void dequeue(Queue *queue);
void enqueue(Queue *queue, int adding);
#endif
