#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#include <pthread.h>

struct row *createArray(int numOfElements);

void printGraph(struct row *graph, int numberOfElements);

void warshalls(struct row *boolMatrix, struct row *warPath, int numberOfElements, int numberOfThreads);

void warshallsThreaded(struct row *boolMatrix, struct row *warPath, int numberOfElements, int numberOfThreads);

void warshallsProcessed(struct row *boolMatrix, struct row *warPath, int numberOfElements, int numberOfThreads);

void bagOfTask(struct row *boolMatrix, struct row *warPath, int numberOfElements);

/*contains a row of the matrix*/
struct row
{
	int *edgeNums;
	pthread_mutex_t *lock;
};

/*makes a linked list for Queue operations*/
struct rowList
{
	struct row* element;
	struct rowList* next;
};

struct Queue
{
	int cap;
	int size;
	struct rowList* head;
	struct rowList* tail;
};

/*struct is to be used when passing multiple args to the thread method*/
struct Params
{
	int k;
	int numEdges;
	int thread_num;
	struct row* edge_ptr;
};



void threadedWarshall(struct row *warPath,int threadnum,int numEdges);
struct row createRow(int numberOfEdges);
struct Queue * createQueue(int elementsMax);
void destroyQueue(struct Queue *removed);
struct row* dequeue(struct Queue * queue);
void enqueue(struct Queue *queue, struct row *element);
void freeAll(struct row *boolMatrix, struct row *warPath, int size);
void *bagIt(void *params);
void warshallsProcessed_bt(struct row* boolMatrix, struct row* warPath, int numEdges, int numProcess);
void bagOfThreads_bt(struct row* boolMatrix, struct row* warPath, int numEdges, int numProcess);
#endif

