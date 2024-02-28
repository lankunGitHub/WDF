#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 4
void swap(int arr[], int i, int k) {
    arr[i] = arr[i] ^ arr[k];
    arr[k] = arr[i] ^ arr[k];
    arr[i] = arr[i] ^ arr[k];
}
// 关于冒泡(O(n^2),稳定)
void bubbleSort(int arr[], int size) {
    int flag;
    for (int i = 0; i < size - 1; i++) {
        flag = 0;
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr, j, j + 1);
                flag = 1;
            }
        }
        if (flag == 0) {
            break;
        }
    }
}
//关于选择(O(n^2),不稳定)
void selectSort(int arr[],int size)
{
    for(int i=0;i<size;i++)
    {
        int loc=i;
        for(int k=i;k<size;k++)
            if(arr[loc]>arr[k])  loc=k;
        sawp(arr,loc,i);
    }
}
// 关于归并的内容(O(N*logN)稳定)
void merge(int arr[], int L, int R, int mid) {
    int* help = (int*)malloc(sizeof(int) * (R - L + 1));
    int i = 0, p1 = L, p2 = mid + 1;
    while (p1 <= mid && p2 <= R)
        help[i++] = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];
    while (p1 <= mid)
        help[i++] = arr[p1++];
    while (p2 <= R)
        help[i++] = arr[p2++];
    for (int k = L; k < i; k++)
        arr[k] = help[k];
    free(help);
}
void mergeSort(int arr[], int L, int R) {
    int mid = L + ((R - L) >> 1);
    if (L == R)
        return;
    mergeSort(arr, L, mid);
    mergeSort(arr, mid + 1, R);
    merge(arr, L, R, mid);
}
// 关于堆的内容(O(N*logN)不稳定)
typedef struct Heap {
    int* array;
    int currentSize;
    int maxSize;
} MinHeap;

MinHeap* initHeap(int size) {
    MinHeap* minheap = (MinHeap*)malloc(sizeof(MinHeap));
    if (minheap == NULL)
        return;
    minheap->array = (int*)malloc(sizeof(int) * size);
    minheap->currentSize = 0;
    minheap->maxSize = size;
    return minheap;
}
void destroyHeap(MinHeap* minheap) {
    free(minheap->array);
    free(minheap);
}
void heapifyUp(MinHeap* minheap, int index) {
    int* array = minheap->array;
    while (index >= 1 && array[index] < array[(index - 1) / 2]) {
        swap(array, index, (index - 1) / 2);
        index = (index - 1) / 2;
    }
}
void heapifyDown(MinHeap* minheap, int index) {
    int leftchild = index * 2 + 1;
    int rightchild = index * 2 + 2;
    int smallest = index;
    if (leftchild < minheap->currentSize &&
        minheap->array[smallest] > minheap->array[leftchild])
        smallest = leftchild;
    if (rightchild < minheap->currentSize &&
        minheap->array[smallest] > minheap->array[rightchild])
        smallest = rightchild;
    if (index != smallest)
        swap(minheap->array, index, smallest);
    heapifyDown(minheap, smallest);
}
void heapInsert(MinHeap* minheap, int value) {
    if (minheap->currentSize == minheap->maxSize)
        return;
    minheap->array[minheap->currentSize] = value;
    heapifyUp(minheap, minheap->currentSize);
    minheap->currentSize++;
}
int extractMin(MinHeap* minheap) {
    int minValue = minheap->array[0];
    minheap->array[0] = minheap->array[minheap->currentSize - 1];
    minheap->currentSize--;
    return minValue;
}

// 关于桶排的内容(后补)

int main(void) {
    int arr[SIZE];
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 10;
        printf("%d  ", arr[i]);
    }
    printf("\n");
    return 0;
}