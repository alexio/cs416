#ifndef OPERATIONS_H_
#define OPERATIONS_H_

struct node {
	int *name;
	struct node *next;
}; 
typedef struct node *node_ptr;

struct adjLL {
	struct node *next;
};
typedef struct adjLL *adjLL_ptr;

struct node *createNode(int name);

int createEdge(struct node **array, int currentx, int currenty, struct node *newEdge);

void addNodeToList(struct node **array , struct node *newNode,int currentPos);

int alreadyInList(/*struct adjLL * head , struct node *checkThisNode*/struct node * matchingNode , struct node **array);

struct node **createArray(int numOfElements);

#endif