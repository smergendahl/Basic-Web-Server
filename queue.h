#include "cs537.h"

typedef struct Node {
	volatile int value;
	struct Node *next;
} Node;

typedef struct Queue {
	Node *head;
	int size;
} Queue;

void queue_init(Queue *Q);
void enqueue(Queue *Q, int value);
int dequeue(Queue *Q);
void print_queue(Queue *Q);
