#include<stdio.h>
typedef struct Node{
    int data;
    struct Node* llink;
    struct Node* rlink;
}Node;

typedef struct ArrayStack{
    struct Node* node;          //indicate last inserted node
    int dataCount;
}ArrayStack;

void init(ArrayStack* stack) {
    stack->dataCount = 0;
    stack->node = NULL;
}
int isEmpty(ArrayStack* stack) {
    return stack->dataCount == 0;
}
int size(ArrayStack* stack) {
    return stack->dataCount;
}
void push(ArrayStack* stack, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode){
        printf("error\n");
        return;
    }
    newNode->data = data;
    stack->dataCount++;

    if(stack->node == NULL){
        newNode->llink = NULL;
        newNode->rlink = NULL;
        stack->node = newNode;
    }else{
        newNode->llink = stack->node;
        newNode->rlink = NULL;
        stack->node = newNode;
    }
}
int pop(ArrayStack* stack) {
    if (isEmpty(stack)) {
        printf("stack is empty!!\n\n");
        return;
    }
    int data = stack->node->data;
    stack->node = stack->node->llink;
    stack->node->rlink = NULL;
    stack->dataCount--;
    free(stack->node->rlink);
    return data;
}
int peek(ArrayStack* stack) {
    return stack->node->data;
}

int main() {
    ArrayStack* stack = (ArrayStack*)malloc(sizeof(ArrayStack));
    init(stack);

    printf("is empty? %s\n", isEmpty(stack) == 1 ? "yes" : "no");
    for (int i = 0; i < 5; i++)
        push(stack, i + 1);

    printf("\n<Data inserted>\n");
    printf("is empty? %s\n", isEmpty(stack) == 1 ? "yes" : "no");
    printf("size : %d\n\n", size(stack));
    push(stack, 100);

    for (int i = 0; i < 3; i++)
        printf("%d ", pop(stack));
    printf("\n");

    printf("size : %d\n", size(stack));
    printf("peek : %d\n", peek(stack));

    return 0;
}