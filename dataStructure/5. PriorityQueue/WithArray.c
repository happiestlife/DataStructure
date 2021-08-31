#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 10
void insert(int* queue, int data, int index){
    if(data > queue[0]){
        for (int i = index-1; i >= 0; i--)
            queue[i + 1] = queue[i];
        queue[0] = data;
    }else if(data < queue[index-1]){
        queue[index] = data;
    }else{
        for (int i = 0; i < index; i++) {
            if(queue[i] > data && queue[i+1] < data){
                for (int j = index-1; j >= i+1; j--)
                    queue[j + 1] = queue[j];
                queue[i+1] = data;
                break;
            }
        }
    }
}

int delete(int* queue, int data){
    int index = binarySearch(queue, data);
    if (index == -1) {
        printf("there is no data\n");
        return -1;
    }
    for (int i = index; i < MAX_SIZE - 1; i++) 
        queue[i] = queue[i + 1];
    return 1;
}

int binarySearch(int* queue, int data){
    int left = 0;
    int right = MAX_SIZE - 1;

    while (left <= right) {
        int mid = (left + right)/2;
        if (queue[mid] == data) {
            return mid;
        }
        else if (queue[mid] > data) {
            left = mid + 1;
        }
        else
            right = mid - 1;
    }
    return -1;
}
void printQueue(int* queue, int dataNum) {
    for (int i = 0; i < dataNum; i++)
        printf("%d ", queue[i]);
    printf("\n");
}

int main(){
    int priorityQueue[MAX_SIZE] = { 0 };
    int queueDataNum = 0;
    char noSameData = 1;
    for(int i = 0; i < MAX_SIZE;){
        int data = rand()%10 + 1;
        for (int j = 0; j < i; j++) {
            if (priorityQueue[j] == data) {
                noSameData = 0;
                break;
            }
        }

        if(noSameData){
            insert(priorityQueue, data, i);
            printQueue(priorityQueue, queueDataNum);
            queueDataNum++;
            i++;
        }

        noSameData = 1;
    }

    printf("\n");
    printQueue(priorityQueue, queueDataNum);

    int searchTest[2] = { 7, 13 };
    for (int i = 0; i < 2; i++) {
        int trueOrFalse = binarySearch(priorityQueue, searchTest[i]);
        if (trueOrFalse != -1) {
            printf("Index of %d  is %d.\n",searchTest[i], trueOrFalse + 1);
        }
        else
            printf("there is no %d.\n", searchTest[i]);
    }
    printf("\n");

    int deleteTest[2] = { 2, -1 };
    for (int i = 0; i < 2; i++) {
        int trueOrFalse = delete(priorityQueue, deleteTest[i]);
        if (trueOrFalse != -1) {
            printQueue(priorityQueue, --queueDataNum);
        }
    }
}