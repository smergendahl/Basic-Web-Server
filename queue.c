#include "queue.h"

void queue_init(Queue *Q) {
	Q->head = NULL;
	Q->size = 0;
}

void enqueue(Queue *Q, int value) {
	Node *new_node; 
	new_node = (Node *) malloc(sizeof(Node));
	if (new_node == NULL) {
		unix_error("malloc error");
	}

	new_node->value = value;
	new_node->next = NULL;
	Node *temp = Q->head;
	if (Q->head == NULL) {
		Q->head = new_node;
	} else {
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = new_node;
	}
	Q->size++;
}

int dequeue(Queue *Q) {
	int retval;
	if (Q->size == 0) {
		printf("queue is empty, could not dequeue\n");
		return -1;
	} 
	else if (Q->size == 1) {
		retval = Q->head->value;
		free(Q->head);
		Q->head = NULL;
		Q->size--;
		return retval;
	} else {
		retval = Q->head->value;
		Node *temp = Q->head;
		Q->head = Q->head->next;
		free(temp);
		Q->size--;
		return retval;
	}
}

void print_queue(Queue *Q) {
	Node *temp = Q->head;
	if (Q->size == 0) {
		printf("queue is empty\n");
		return;
	}
	while (temp) {
		printf("%d\n", temp->value);
		temp = temp->next;
	}
}
