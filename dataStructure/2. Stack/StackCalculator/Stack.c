#include"Stack.h"

int isStackEmpty(StackInfo* stackInfo) {
    return stackInfo->first == NULL;
}

void push(StackInfo* head, char operation) {
    StackData* newNode = (StackData*)malloc(sizeof(StackData));
    if (!newNode) {
        printf("error\n");
        return;
    }

    newNode->Soperation = operation;

    if (head->first == NULL) {
        head->first = head->last = newNode;
        newNode->rlink = newNode->llink = NULL;
    }
    else {
        head->last->rlink = newNode;
        newNode->llink = head->last;
        head->last = newNode;
        newNode->rlink = NULL;
    }
}

char pop(StackInfo* stackInfo) {
    if (stackInfo->first == NULL) {
        printf("no data\n");
        return;
    }
    StackData* tmp = stackInfo->last;
    char data = tmp->Soperation;
    stackInfo->last = tmp->llink;
    if (stackInfo->last == NULL) stackInfo->first = NULL;
    free(tmp);
    return data;
}

char peek(StackInfo* stackInfo) {
    if (stackInfo->first == NULL) {
        printf("no data\n");
        return;
    }
    return stackInfo->last->Soperation;
}