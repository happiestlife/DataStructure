#include<stdio.h>
#define SIZE 5
typedef struct QueueArray {
	int data[SIZE];
	int front;
	int back;
}QueueArray;
void init(QueueArray* queueArray) {
	queueArray->front = queueArray->back = -1;
}
int isEmpty(QueueArray* queueArray) {
	return queueArray->front == queueArray->back;
}
int isFull(QueueArray* queueArray) {
	return queueArray->back == SIZE - 1;
}
void enqueue(QueueArray* queueArray, int data) {
	if (isFull(queueArray)) {
		printf("data is full\n");
		return;
	}
	queueArray->data[++queueArray->back] = data;
}
int dequeueu(QueueArray* queueArray) {
	if (isEmpty(queueArray)) {
		printf("no data\n");
		return;
	}
	return queueArray->data[++queueArray->front];
}
int peek(QueueArray* queueArray) {
	if (isEmpty(queueArray)) {
		printf("no data\n");
		return;
	}
	return queueArray->data[queueArray->front+1];
}
void printAll(QueueArray* queueArray) {
	for (int i = queueArray->front+1; i < queueArray->back; i++)
		printf("%d ", queueArray->data[i]);
	printf("\n");
}
int main() {
	QueueArray* queueArray = (QueueArray*)malloc(sizeof(QueueArray));
	if (!queueArray) {
		printf("error\n");
		return 0;
	}
	init(queueArray);
	for (int i = 0; i < SIZE; i++)
		enqueue(queueArray, (i + 1) * 10);
	printAll(queueArray);
	printf("\n");

	printf("peek : %d\n", peek(queueArray));
	for (int i = 0; i < 3; i++)
		printf("dequeue : %d\n", dequeueu(queueArray));
	printAll(queueArray);
	printf("\n");
}