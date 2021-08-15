#include<stdio.h>
#define MAX_SIZE 10
typedef struct {
    int data[MAX_SIZE];
    int dataCount;
}ArrayStack;

void init(ArrayStack* stack) {
    stack->dataCount = 0;
}
int isEmpty(ArrayStack* stack) {
    return stack->dataCount == 0;
}
int isFull(ArrayStack* stack) {
    return stack->dataCount == MAX_SIZE;
}
int size(ArrayStack* stack) {
    return stack->dataCount;
}
void push(ArrayStack* stack, int data) {
    if (isFull(stack)) {
        printf("stack is full!!\n\n");
        return;
    }
    stack->data[(stack->dataCount)++] = data;
}
int pop(ArrayStack* stack) {
    if (isEmpty(stack)) {
        printf("stack is empty!!\n\n");
        return;
    }
    return stack->data[--stack->dataCount];
}
int peek(ArrayStack* stack) {
    return stack->data[stack->dataCount];
}

int main() {
    ArrayStack* stack = (ArrayStack*)malloc(sizeof(ArrayStack));
    init(stack);

    printf("is empty? %s\n", isEmpty(stack) == 1 ? "yes" : "no");
    printf("is full? %s\n", isFull(stack) == 1 ? "yes" : "no");
    for (int i = 0; i < MAX_SIZE; i++)
        push(stack, i + 1);

    printf("\n<Data inserted>\n");
    printf("is empty? %s\n", isEmpty(stack) == 1 ? "yes" : "no");
    printf("is full? %s\n", isFull(stack) == 1 ? "yes" : "no");
    printf("size : %d\n\n", size(stack));
    push(stack, 100);

    for (int i = 0; i < MAX_SIZE - 3; i++)
        printf("%d ", pop(stack));
    printf("\n");

    printf("size : %d\n", size(stack));
    printf("peek : %d\n", peek(stack));

    return 0;
}