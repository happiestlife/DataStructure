#include"Sort.h"

void makeArr(int* arr){
    char noSameData = 1;
    for(int i = 0; i < MAX_SIZE;){
        int data = rand()%MAX_SIZE + 1;

        for(int j = 0; j < i; j++){
            if(arr[j] == data){
                noSameData = 0;
                break;
            }
        }

        if(noSameData)
            arr[i++] = data;

        noSameData = 1;
    }
}

void copy(int* arr, int* copied) {
    for (int i = 0; i < MAX_SIZE; i++)
        copied[i] = arr[i];
}

int main(){
    int arr[MAX_SIZE];
    int tmp[MAX_SIZE];

    srand(1011111);
    makeArr(arr);
    printf("<Before Sorting>\n");
    printArr(arr);
    printf("\n");

    copy(arr, tmp);
    printf("<Merge Sort>\n");
    mergeSort(tmp, 0, MAX_SIZE-1);
    printArr(tmp);

    copy(arr, tmp);
    printf("<Quick Sort>\n");
    quickSort(tmp, 0, MAX_SIZE - 1);
    printArr(tmp);

    copy(arr, tmp);
    printf("<Heap Sort>\n");
    heapSort(tmp);
    printArr(tmp);
}