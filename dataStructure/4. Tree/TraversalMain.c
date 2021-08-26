#include<stdio.h>
#include"Traversal.h"
Queue* queueInit() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->back = queue->front = NULL;
    return queue;
}

void push(Queue* queue, Tree* data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (!newNode) {
        printf("error\n");
        return;
    }
    newNode->data = data;
    newNode->link = NULL;

    if (queue->front == NULL) {
        queue->front = newNode;
        queue->back = newNode;
    }else {
        queue->back->link = newNode;
        queue->back = newNode;
    }
}

Tree* pop(Queue* queue) {
    if (queue->front == NULL) {
        printf("queue is empty\n");
        return;
    }
    QueueNode* tmp = queue->front;
    queue->front = queue->front->link;
    Tree* poppedData = tmp->data;
    free(tmp);
    return poppedData;
}

void level(Tree* root) {
    if (root == NULL) return;
    Queue* queue = queueInit();
    push(queue, root);
    while (queue->front != NULL) {
        root = pop(queue);
        printf("%d ", root->data);
        if(root->left != NULL)
            push(queue, root->left);
        if (root->right != NULL)
            push(queue, root->right);
    }
}

void makeTree(Tree* root, int maxLevel) {
    if (maxLevel > root->level) {
        root->left = (Tree*)malloc(sizeof(Tree));
        root->left->data = root->data * 2;
        root->left->level = root->level + 1;
        root->left->left = root->left->right = NULL;

        root->right = (Tree*)malloc(sizeof(Tree));
        root->right->data = root->data * 2 + 1;
        root->right->level = root->level + 1;
        root->right->left = root->right->right = NULL;

        makeTree(root->left, maxLevel);
        makeTree(root->right, maxLevel);
    }
}

int main(){
    Tree* root = (Tree*)malloc(sizeof(Tree));
    if (!root) {
        printf("error\n");
        return;
    }
    root->data = 1;
    root->level = 1;
    makeTree(root,  3);

    printf("<level>\n");
    level(root);
    printf("\n\n<preorder>\n");
    preOrder(root);
    printf("\n\n<inOrder>\n");
    inOrder(root);
    printf("\n\n<postOrder>\n");
    postOrder(root);
}