#include"Sort.h"
void insertionSort(int* arr, int size){
    int i, j;
    for(i = 1; i < size; i++){
        int data = arr[i];
        for(j = i-1; arr[j] > data && j >= 0; j--){
            arr[j+1] = arr[j];
        }
        arr[j+1] = data;
    }
}

void selectionSort(int* arr, int size){
    int least, tmp;
    for(int i = 0; i < size-1; i++){
        least = i;
        for(int j = i+1; j < size; j++)
            if(arr[least] > arr[j])
                least = j;
        if(least != i){
            tmp = arr[i];
            arr[i] = arr[least];
            arr[least] = tmp;
        }
    }
}

void shellSort(int* arr){
    int interval = 5;
    int *sorting = NULL;     
    while(interval != 0){
        int size = MAX_SIZE / interval;
        if(MAX_SIZE % interval != 0) size++;
        sorting = (int)malloc(sizeof(int) * size);

        int sortingIndex = 0;
        for(int j = 0; j < interval; j++){
            for (int k = 0; k < MAX_SIZE; k++)
                if (k % interval == j)
                    sorting[sortingIndex++] = arr[k];

            insertionSort(sorting, sortingIndex);

            for(int k = 0; k < sortingIndex; k++)
                arr[k*interval + j] = sorting[k];

            sortingIndex = 0;
        }

        free(sorting);
        interval /= 2;
    }
}
