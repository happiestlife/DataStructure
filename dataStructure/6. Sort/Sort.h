#include<stdio.h>
#define MAX_SIZE 10

#define HEAP_SIZE MAX_SIZE+1
typedef struct Node {
    int data;
}Node;
typedef struct Heap {
    Node heapData[HEAP_SIZE];
    int size;
}Heap;

void insertionSort(int* arr, int size);
void selectionSort(int* arr, int size);
void shellSort(int* arr);
void bubbleSort(int* arr, int size);
void merge(int* arr, int start, int mid, int end);
void mergeSort(int* arr, int start, int end);
void quickSort(int* arr, int start, int end);
int partition(int* arr, int start, int end);
void printArr(int* arr);