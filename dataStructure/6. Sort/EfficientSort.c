#include"Sort.h"
void mergeSort(int* arr, int start, int end){
    //printf("%d(s) %d(e) ", start, end);
    if(start < end){
        int mid = (start + end + 1) / 2;
        //printf("%d(mid) => left ", mid);
        mergeSort(arr, start, mid-1);
        //printf("%d(mid) => right\n", mid);
        mergeSort(arr, mid , end);
        merge(arr, start, mid, end);
    }
}
void merge(int* arr, int start, int mid, int end){
    int arr1Index = 0, arr2Index = mid;
    int arr1End = mid-1, arr2End = end;

    int result[MAX_SIZE];
    int arrIndex = start;
    printf("arr1 %d, arr2 %d\n", arr1End, arr2End);
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
        printf("%d ", result[i]);
    printf("\n %d(s) %d(arrIndex)\n", start, arrIndex);

    for (int i = start; i < arrIndex; i++)
        arr[i] = result[i];

    printf("\n");
    printArr(arr);
    printf("\n");
}
