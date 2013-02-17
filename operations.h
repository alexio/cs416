#ifndef OPERATIONS_H_
#define OPERATIONS_H_

struct row *createArray(int numOfElements);

void printGraph(struct row *graph, int numberOfElements);

void warshalls(struct row *boolMatrix, struct row *warPath, int numberOfElements, int numberOfThreads);

void bagOfTask(struct row *boolMatrix, struct row *warPath, int numberOfElements);

struct Queue
{
	int cap;
	int size;
	int head;
	int tail;
	int * elements;
};

struct row
{
	int *edgeNums;
	pthread_mutex_t *lock;
};

struct row createRow(int numberOfEdges);
struct Queue * createQueue(int elementsMax);
void destroyQueue(struct Queue *removed);
void dequeue(struct Queue *queue);
void enqueue(struct Queue *queue, int adding);
void freeAll(struct row *boolMatrix, struct row *warPath, int size);
#endif
