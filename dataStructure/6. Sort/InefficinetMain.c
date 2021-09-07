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

void printArr(int* arr) {
    for (int i = 0; i < MAX_SIZE; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void copy(int* arr, int* copied) {
    for (int i = 0; i < MAX_SIZE; i++)
        copied[i] = arr[i];
}

int main(){
    int arr[MAX_SIZE];
    int tmp[MAX_SIZE];

    makeArr(arr);
    printf("<Before Sorting>\n");
    printArr(arr);
    printf("\n");

    copy(arr, tmp);
    printf("<Insertion Sort>\n");
    insertionSort(tmp, MAX_SIZE);
    printArr(tmp);

    copy(arr, tmp);
    printf("<Selection Sort>\n");
    selectionSort(tmp, MAX_SIZE);
    printArr(tmp);

    copy(arr, tmp);
    printf("<Shell Sort>\n");
    shellSort(tmp);
    printArr(tmp);

    copy(arr, tmp);
    printf("<Bubble Sort>\n");
    bubbleSort(tmp, MAX_SIZE);
    printArr(tmp);
}