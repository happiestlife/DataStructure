typedef struct Tree{
    int data;
    int level;
    struct Tree* left,* right;
}Tree; 
typedef struct QueueNode{
    Tree* data;
    struct QueueNode* link;
}QueueNode;
typedef struct Queue {
    struct QueueNode* front;
    struct QueueNode* back;
}Queue;

void preOrder(Tree* root);
void inOrder(Tree* root);
void postOrder(Tree* root);