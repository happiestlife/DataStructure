#include<stdio.h>
#define SIZE 5
typedef struct Node {
	int data;
	struct Node* llink;
	struct Node* rlink;
}Node;
typedef struct Deque {
	struct Node* front;
	struct Node* back;
}Deque;

void init(Deque* deque) {
	deque->front = deque->back = NULL;
}
int isEmpty(Deque* deque) {
	return deque->front == NULL;
}
void enqueueFront(Deque* deque, int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (!newNode) {
		printf("error\n");
		return;
	}
	newNode->data = data;

	if (deque->front == NULL) {
		deque->front = deque->back = newNode;
		newNode->llink = newNode->rlink = NULL;
	}
	else {
		newNode->rlink = deque->front;
		newNode->llink = deque->back;
		deque->back->rlink = newNode;
		deque->front->llink;
	}
	deque->front = newNode;
}
void enqueueBack(Deque* deque, int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (!newNode) {
		printf("error\n");
		return;
	}
	newNode->data = data;

	if (deque->front == NULL) {
		deque->front = deque->back = newNode;
		newNode->llink = newNode->rlink = NULL;
	}
	else {
		newNode->rlink = deque->front;
		newNode->llink = deque->back;
		deque->back->rlink = newNode;
		deque->front->llink;
	}
	deque->back = newNode;
}
int dequeueFront(Deque* deque) {
	if (isEmpty(deque)) {
		printf("no data\n");
		return;
	}
	Node* tmp = deque->front;
	int data = tmp->data;
	deque->front = deque->front->rlink;
	deque->front->llink = deque->back;
	deque->back->rlink = deque->front;
	free(tmp);
	return data;
}
int dequeueBack(Deque* deque) {
	if (isEmpty(deque)) {
		printf("no data\n");
		return;
	}
	Node* tmp = deque->back;
	int data = tmp->data;
	deque->back = deque->back->llink;
	deque->back->rlink = deque->front;
	deque->front->llink = deque->back;
	free(tmp);
	return data;
}
int peekFront(Deque* deque) {
	if (isEmpty(deque)) {
		printf("no data\n");
		return;
	}
	return deque->front->data;
}
int peekBack(Deque* deque) {
	if (isEmpty(deque)) {
		printf("no data\n");
		return;
	}
	return deque->back->data;
}
char search(Deque* deque, int data) {
	if (isEmpty(deque)) {
		printf("no data\n");
		return;
	}
	Node* index = deque->front;
	while (1) {
		if (index->data == data)
			return 1;
		index = index->rlink;
		if (index == deque->front) break;
	}
	return 0;
}
void printAll(Deque* deque) {
	Node* index = deque->front;
	do {
		printf("%d ", index->data);
		index = index->rlink;
	} while (index != deque->front);
	printf("\n");
}
int main() {
	Deque* deque = (Deque*)malloc(sizeof(Deque));
	if (!deque) {
		printf("error\n");
		return 0;
	}
	init(deque);
	for (int i = 0; i < SIZE; i++)
		enqueueFront(deque, (i + 1) * 10);
	for (int i = 0; i < SIZE; i++)
		enqueueBack(deque, (i + 1 + SIZE) * 10);
	printAll(deque);
	printf("\n");

	printf("peekFront peekBack : %d %d\n", peekFront(deque), peekBack(deque));
	printf("is there 40? %s\n\n", search(deque, 40) == 1 ? "yes" : "no");
	
	for (int i = 0; i < 3; i++) 
		printf("dequeueFront dequeueBack : %d %d\n", dequeueFront(deque), dequeueBack(deque));
	
	printAll(deque);
}