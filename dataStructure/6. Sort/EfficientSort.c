#include"Sort.h"
void mergeSort(int* arr, int start, int end){
    if(start < end){
        int mid = (start + end + 1) / 2;
        mergeSort(arr, start, mid-1);
        mergeSort(arr, mid , end);
        merge(arr, start, mid, end);
    }
}

void merge(int* arr, int start, int mid, int end){
    int arr1Index = start, arr2Index = mid;
    int arr1End = mid-1, arr2End = end;

    int result[MAX_SIZE];
    int arrIndex = start;
    while(arr1Index <= arr1End && arr2Index <= arr2End){
        if(arr[arr1Index] < arr[arr2Index])
            result[arrIndex++] = arr[arr1Index++];
        else 
            result[arrIndex++] = arr[arr2Index++];
    }
    while(arr1Index <= arr1End){
        result[arrIndex++] = arr[arr1Index++];
    }

    while(arr2Index <= arr2End){
        result[arrIndex++] = arr[arr2Index++];
    }

    for (int i = start; i < arrIndex; i++)
        arr[i] = result[i];
}

void quickSort(int* arr, int start, int end){
    if(start < end){
        int pivot = partition(arr, start, end);
        quickSort(arr, start, pivot-1);
        quickSort(arr, pivot+1, end);
    }
}

int partition(int* arr, int start, int end) {
    int pivot = start;
    int left = start, right = end + 1;
    while (left < right) {
        do {
            left++;
        } while (arr[left] < arr[pivot] && left <= right);
        do {
            right--;
        } while (arr[right] > arr[pivot] && right >= left);
        if (left < right) {
            int tmp = arr[left];
            arr[left] = arr[right];
            arr[right] = tmp;
        }
    }

    int tmp = arr[right];
    arr[right] = arr[pivot];
    arr[pivot] = tmp;

    pivot = right;

    return pivot;
}

void heapInit(Heap* heap) {
    heap->size = 0;
    heap->heapData[0].data = 0;
}

void printHeap(Heap* heap) {
    for (int i = 1; i < heap->size+1; i++)
        printf("%d ", heap->heapData[i].data);
    printf("\n");
}

void insert(Heap* heap, int data) {
    heap->heapData[++(heap->size)].data = data;
    if (heap->size == 1)return;
    int i = heap->size;
    while (heap->heapData[i / 2].data < data && i != 1) {
        int tmp = heap->heapData[i / 2].data;
        heap->heapData[i / 2].data = data;
        heap->heapData[i].data = tmp;
        i = i / 2;
    }
}

int delete(Heap* heap) {
    if (heap->size == 0) {
        printf("there is no data\n");
        return;
    }
    int root = heap->heapData[1].data;
    heap->heapData[1] = heap->heapData[heap->size--];
    int i = 1;
    while (i * 2 + 1 <= heap->size && (heap->heapData[i * 2].data > heap->heapData[i].data || heap->heapData[i * 2 + 1].data > heap->heapData[i].data)) {
        if (heap->heapData[i * 2].data > heap->heapData[i * 2 + 1].data) {
            int tmp = heap->heapData[i].data;
            heap->heapData[i].data = heap->heapData[i * 2].data;
            heap->heapData[i * 2].data = tmp;
            i = i * 2;
        }
        else {
            int tmp = heap->heapData[i].data;
            heap->heapData[i].data = heap->heapData[i * 2 + 1].data;
            heap->heapData[i * 2 + 1].data = tmp;
            i = i * 2 + 1;
        }
    }
    return root;
}

void heapSort(int* arr) {
    Heap* maxHeap = (Heap*)malloc(sizeof(maxHeap));
    if (!maxHeap) {
        printf("error\n");
        return;
    }
    heapInit(maxHeap);
    for (int i = 0; i < MAX_SIZE; i++)
        insert(maxHeap, arr[i]);

    for (int i = MAX_SIZE - 1; i >= 0; i--)
        arr[i] = delete(maxHeap);
    
}

void printArr(int* arr) {
    for (int i = 0; i < MAX_SIZE; i++)
        printf("%d ", arr[i]);
    printf("\n");
}