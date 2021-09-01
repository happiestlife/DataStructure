#include<stdio.h>
#define MAX_SIZE 11
typedef struct Node{
    int data;
}Node;
typedef struct Heap{
    Node heapData[MAX_SIZE];
    int size;
}Heap;
void heapInit(Heap* heap){
    heap->size = 0;
    heap->heapData[0].data = 0;
}
void insert(Heap* heap, int data){
    heap->heapData[++(heap->size)].data = data;
    if (heap->size == 1)return;
    int i = heap->size;
    while(heap->heapData[i/2].data < data && i != 1){
        int tmp = heap->heapData[i/2].data;
        heap->heapData[i/2].data = data;
        heap->heapData[i].data = tmp;
        i = i / 2;
    }
}

void delete(Heap* heap){
    if (heap->size == 0) {
        printf("there is no data\n");
        return;
    }
    heap->heapData[1] = heap->heapData[heap->size--];
    int i = 1;
    while (i * 2 <= heap->size && heap->heapData[i * 2].data > heap->heapData[i].data || heap->heapData[i * 2 + 1].data > heap->heapData[i].data) {
        if (heap->heapData[i * 2].data > heap->heapData[i * 2 + 1].data) {
            int tmp = heap->heapData[i].data;
            heap->heapData[i].data = heap->heapData[i*2] .data;
            heap->heapData[i*2].data = tmp;
            i = i * 2;
        }else{
            int tmp = heap->heapData[i].data;
            heap->heapData[i].data = heap->heapData[i*2+1] .data;
            heap->heapData[i*2+1].data = tmp;
            i = i * 2 + 1;
        }
    }
}

void printHeap(Heap* heap){
    for(int i = 1; i < MAX_SIZE; i++)
        printf("%d ", heap->heapData[i].data);
    printf("\n");
}

int main(){
    int input[MAX_SIZE];
    int noSameData = 1;
    for(int i = 0; i < MAX_SIZE-1;){
        int data = rand()%10 + 1;
        for (int j = 0; j < i; j++) {
            if (input[j] == data) {
                noSameData = 0;
                break;
            }
        }

        if(noSameData){ 
            input[i] = data;
            printf("%d ", input[i]);
            i++;
        }

        noSameData = 1;
    }
    printf("\n");

    Heap* maxHeap = (Heap*)malloc(sizeof(maxHeap));
    if (!maxHeap) {
        printf("error\n");
        return;
    }
    heapInit(maxHeap);
    for(int i = 1; i < MAX_SIZE; i++)
        insert(maxHeap, input[i - 1]);
    printHeap(maxHeap);
    printf("\n");

    delete(maxHeap);
    printHeap(maxHeap);
    printf("\n");
}