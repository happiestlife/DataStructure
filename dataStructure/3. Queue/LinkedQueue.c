#include<stdio.h>
#define SIZE 5
typedef struct Node {
	int data;
	struct Node* link;
}Node;
typedef struct LinkedQueue {
	struct Node* front;
	struct Node* back;
}LinkedQueue;

void init(LinkedQueue* linkedQueue) {
	linkedQueue->front = linkedQueue->back = NULL;
}
int isEmpty(LinkedQueue* linkedQueue) {
	return linkedQueue->front == linkedQueue->back;
}
void enqueue(LinkedQueue* linkedQueue, int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (!newNode) {
		printf("error\n");
		return;
	}
	newNode->data = data;
	newNode->link = NULL;

	if (linkedQueue->front == NULL) {
		linkedQueue->front = linkedQueue->back = newNode;
	}else {
		linkedQueue->back->link = newNode;
		linkedQueue->back = newNode;
	}
}
int dequeueu(LinkedQueue* linkedQueue) {
	if (isEmpty(linkedQueue)) {
		printf("no data\n");
		return;
	}
	Node* tmp = linkedQueue->front;
	int data = tmp -> data;
	linkedQueue->front = linkedQueue->front->link;
	free(tmp);
	return data;
}
int peek(LinkedQueue* linkedQueue) {
	if (isEmpty(linkedQueue)) {
		printf("no data\n");
		return;
	}
	return linkedQueue->front->data;
}
void printAll(LinkedQueue* linkedQueue) {
	for (Node* i = linkedQueue->front; i; i = i->link)
		printf("%d ", i->data);
	printf("\n");
}
int main() {
	LinkedQueue* linkedQueue = (LinkedQueue*)malloc(sizeof(LinkedQueue));
	if (!linkedQueue) {
		printf("error\n");
		return 0;
	}
	init(linkedQueue);
	for (int i = 0; i < SIZE; i++)
		enqueue(linkedQueue, (i + 1) * 10);
	printAll(linkedQueue);
	printf("\n");

	printf("peek : %d\n", peek(linkedQueue));
	for (int i = 0; i < 3; i++)
		printf("dequeue : %d\n", dequeueu(linkedQueue));
	printAll(linkedQueue);
	printf("\n");
}