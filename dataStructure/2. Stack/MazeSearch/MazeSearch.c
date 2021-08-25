#include<stdio.h>
#define SIZE 10
typedef struct MazeMazeStack {
    int x, y;
    struct MazeStack* link;
}MazeStack;

char maze[SIZE][SIZE] = {
    {'1','1','1','1','1','1','1','1','1','1'},
    {'S','0','0','1','0','0','0','0','0','1'},
    {'1','0','1','1','0','1','0','1','0','1'},
    {'1','0','1','1','1','0','0','1','0','1'},
    {'1','0','0','0','1','0','0','1','0','1'},
    {'1','0','1','1','1','1','0','1','0','F'},
    {'1','0','0','0','0','1','0','1','1','1'},
    {'1','0','1','1','1','1','0','1','0','1'},
    {'1','0','0','0','0','0','0','0','0','1'},
    {'1','1','1','1','1','1','1','1','1','1'}
};

MazeStack* createNode(int _x, int _y) {
    MazeStack* newNode = (MazeStack*)malloc(sizeof(MazeStack));
    if (!newNode) {
        printf("error\n");
        return;
    }
    newNode->x = _x;
    newNode->y = _y;
    newNode->link = NULL;

    return newNode;
}
int isEmpty(MazeStack* stack) {
    return stack == NULL;
}

void push(MazeStack** stack, MazeStack* newNode) {
    if (newNode == NULL) return;
    newNode->link = *stack;
    *stack = newNode;
}

MazeStack pop(MazeStack** stack) {
    if (isEmpty(*stack)) {
        printf("MazeStack is empty\n");
        return;
    }
    MazeStack beforeIndex;
    MazeStack* noUseFile = *stack;

    beforeIndex.x = noUseFile->x;
    beforeIndex.y = noUseFile->y;

    *stack = (*stack)->link;
    free(noUseFile);
    return beforeIndex;
}

MazeStack* move(MazeStack* stack, int x, int y) {
    if (x < 0 || y < 0) return NULL;
    if (maze[x][y] != '1' && maze[x][y] != '*') {
        MazeStack* node = createNode(x, y);
        return node;
    }
    return NULL;
}

void printMaze() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) 
            printf(" %c", maze[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main() {
    int x = 1, y = 0;
    char wayChangedFlag = 0;
    int stackBufferIndex;
    MazeStack* stack = NULL;
    MazeStack* stackBuffer[4];

    while (maze[x][y] != 'F') {
        maze[x][y] = '*';
        printMaze();
        stackBuffer[0] = move(stack, x - 1, y);
        stackBuffer[1] = move(stack, x, y - 1);
        stackBuffer[2] = move(stack, x + 1, y);
        stackBuffer[3] = move(stack, x, y + 1);

        for (stackBufferIndex = 0; stackBufferIndex < 4; stackBufferIndex++) {
            if (!wayChangedFlag) {
                if (stackBuffer[stackBufferIndex] != NULL) {
                    x = stackBuffer[stackBufferIndex]->x;
                    y = stackBuffer[stackBufferIndex]->y;
                    wayChangedFlag = 1;
                }
            }
            else {
                if (stackBuffer[stackBufferIndex] != NULL) {
                    push(&stack, stackBuffer[stackBufferIndex]);
                }
            }
        }

        if (!wayChangedFlag) {
            MazeStack indexNode = pop(&stack);
            x = indexNode.x;
            y = indexNode.y;
        }

        wayChangedFlag = 0;
        for (int i = 0; i < 4; i++)
            stackBuffer[i] = NULL;
    }
}