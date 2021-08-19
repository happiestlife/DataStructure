#include<stdio.h>
#define SIZE 5
typedef struct Node {
	int data;
	struct Node* link;
}Node;
typedef struct CircleQueue {
	struct Node* front;
	struct Node* back;
}CircleQueue;

void init(CircleQueue* circleQueue) {
	circleQueue->front = circleQueue->back = NULL;
}
int isEmpty(CircleQueue* circleQueue) {
	return circleQueue->front == NULL;
}
void enqueue(CircleQueue* circleQueue, int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (!newNode) {
		printf("error\n");
		return;
	}
	newNode->data = data;

	if (circleQueue->front == NULL) {
		circleQueue->front = circleQueue->back = newNode;
		newNode->link = newNode;
	}else {
		newNode->link = circleQueue->front;
		circleQueue->back->link = newNode;
		circleQueue->back = newNode;
	}
}
int dequeueu(CircleQueue* circleQueue) {
	if (isEmpty(circleQueue)) {
		printf("no data\n");
		return;
	}
	Node* tmp = circleQueue->front;
	int data = tmp -> data;
	circleQueue->front = circleQueue->front->link;
	circleQueue->back->link = circleQueue->front;
	free(tmp);
	return data;
}
int peek(CircleQueue* circleQueue) {
	if (isEmpty(circleQueue)) {
		printf("no data\n");
		return;
	}
	return circleQueue->front->data;
}
char search(CircleQueue* circleQueue, int data) {
	if (isEmpty(circleQueue)) {
		printf("no data\n");
		return;
	}
	Node* index = circleQueue->front;
	while (1) {
		if (index->data == data)
			return 1;
		index = index->link;
		if (index == circleQueue->front) break;
	}
	return 0;
}
void printAll(CircleQueue* circleQueue) {
	Node* index = circleQueue->front;
	do{
		printf("%d ", index->data);
		index = index->link;
	} while (index != circleQueue->front);
	printf("\n");
}
int main() {
	CircleQueue* circleQueue = (CircleQueue*)malloc(sizeof(CircleQueue));
	if (!circleQueue) {
		printf("error\n");
		return 0;
	}
	init(circleQueue);
	for (int i = 0; i < SIZE; i++)
		enqueue(circleQueue, (i + 1) * 10);
	printAll(circleQueue);
	printf("\n");

	printf("peek : %d\n", peek(circleQueue));
	printf("is there 40? %s\n\n", search(circleQueue, 40) == 1 ? "yes" : "no");

	for (int i = 0; i < 3; i++)
		printf("dequeue : %d\n", dequeueu(circleQueue));
	printAll(circleQueue);
}