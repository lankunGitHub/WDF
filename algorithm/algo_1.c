#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 4
void swap(int arr[], int i, int k)
{
    int temp = arr[i];
    arr[i] = arr[k];
    arr[k] = temp;
}
// 关于冒泡(O(n^2),稳定)
void bubbleSort(int arr[], int size)
{
    int flag;
    for (int i = 0; i < size - 1; i++)
    {
        flag = 0;
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr, j, j + 1);
                flag = 1;
            }
        }
        if (flag == 0)
        {
            break;
        }
    }
}
// 关于选择(O(n^2),不稳定)
void selectSort(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        int loc = i;
        for (int k = i + 1; k < size; k++)
            if (arr[loc] > arr[k])
                loc = k;
        printf("%d  ", arr[loc]);
        swap(arr, loc, i);
        printf("%d  ", arr[i]);
    }
}
// 关于插入排序(O(n^2),稳定)
void insertSort(int arr[], int size)
{
    for (int i = 1; i < size; i++)
    {
        for (int k = i; k >= 0; k--)
        {
            if (arr[k] < arr[k - 1])
                swap(arr, k, k - 1);
        }
    }
}
// 关于归并的内容(O(N*logN)稳定)
void merge(int arr[], int L, int R, int mid)
{
    int *help = (int *)malloc(sizeof(int) * (R - L + 1));
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
void mergeSort(int arr[], int L, int R)
{
    int mid = L + ((R - L) >> 1);
    if (L == R)
        return;
    mergeSort(arr, L, mid);
    mergeSort(arr, mid + 1, R);
    merge(arr, L, R, mid);
}
// 关于堆的内容(O(N*logN)不稳定)
typedef struct Heap
{
    int *array;
    int currentSize;
    int maxSize;
} MinHeap;

MinHeap *initHeap(int size)
{
    MinHeap *minheap = (MinHeap *)malloc(sizeof(MinHeap));
    if (minheap == NULL)
        return;
    minheap->array = (int *)malloc(sizeof(int) * size);
    minheap->currentSize = 0;
    minheap->maxSize = size;
    return minheap;
}
void destroyHeap(MinHeap *minheap)
{
    free(minheap->array);
    free(minheap);
}
void heapifyUp(MinHeap *minheap, int index)
{
    int *array = minheap->array;
    while (index >= 1 && array[index] < array[(index - 1) / 2])
    {
        swap(array, index, (index - 1) / 2);
        index = (index - 1) / 2;
    }
}
void heapifyDown(MinHeap *minheap, int index)
{
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
void heapInsert(MinHeap *minheap, int value)
{
    if (minheap->currentSize == minheap->maxSize)
        return;
    minheap->array[minheap->currentSize] = value;
    heapifyUp(minheap, minheap->currentSize);
    minheap->currentSize++;
}
int extractMin(MinHeap *minheap)
{
    int minValue = minheap->array[0];
    minheap->array[0] = minheap->array[minheap->currentSize - 1];
    minheap->currentSize--;
    return minValue;
}

// 关于桶排的内容(后补)
// 链表
typedef struct Node
{
    int value;
    struct Node *next;
} node;

// 节点的创建

node *creatNode(int value)
{
    node *creat = (node *)malloc(sizeof(node));
    creat->next = NULL;
    creat->value = value;
    return creat;
}
// 头插法插入节点(创建反序链表就可以使用头插法)
void headInsert(node *head, node *insetNode)
{
    insetNode->next = head;
    head = insetNode;
}
// 尾插法插入节点
void tailInsert(node *head, node *insetNode)
{
    if (head = NULL)
    {
        head = insetNode;
        return;
    }
    node *p = head;
    while (p->next != NULL)
        p = p->next;
    p->next = insetNode;
}
//在某个位置插入节点
void locateInsert(node *head,node *insetNode,int location)
{
    if(location==1)
    {
        insetNode->next=head->next;
        insetNode=head;
        return;
    }
    node *p=head->next,*pre=head;
    for(int i=2;i<location;i++)
    {
        pre=pre->next;
        p=p->next;
        if(p==NULL&&i+1<location)
        {
            printf("error");
            return;
        }
    }
    insetNode->next=p;
    pre->next=insetNode;
}
//链表中查找指定节点
int findNode(node *head,int value)
{
    int i=0;
    node *p=head;
    while(head)
    {
        i++;
        if(p->value==value) return i;
        p=p->next;
    }
    return i;
}
//删除某个节点
void deleteNode(node *head,int location)
{
    if(location==1)
    {
        node *dhead=head;
        head=head->next;
        free(dhead);
    }
    node *p=head->next,*pre=head;
    for(int i=2;i<location;i++)
    {
        p=p->next;
        pre=pre->next;
        if(p==NULL)
        {
            printf("error");
            return;
        }
    }
    pre->next=p->next;
    free(p);
}
//将链表翻转
void reverseLinkedList(node *head)
{
    if(head->next==NULL) return;
    else if(head->next->next==NULL)
    {
        node *p=head->next;
        head->next=NULL;
        p->next=head;
        head=p;
        return;
    }
    //方法一：原地反转
    node *pre=head,*cur=head->next;
    printf("%d    %d    %d\n",head->value,pre->value,cur->value);
    while(cur!=NULL)
    {
        pre->next=cur->next;
            printf("%d    %d    %d\n",head->value,pre->value,cur->value);
        cur->next=head;
            printf("%d    %d    %d\n",head->value,pre->value,cur->value);
        head=cur;
            printf("%d    %d    %d\n",head->value,pre->value,cur->value);
        cur=pre->next;
        printf("-------------------------\n");
    }
}

int main(void)
{
    /* int arr[SIZE];
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = rand() % 10;
        printf("%d  ", arr[i]);
    }
    printf("\n");
    printf("\n");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d  ", arr[i]);
    }
    printf("\n");*/


    struct Node* node1 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* node2 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* node3 = (struct Node*)malloc(sizeof(struct Node));

    node1->value = 1;
    node1->next = node2;
    node2->value = 2;
    node2->next = node3;
    node3->value = 3;
    node3->next = NULL;
    // 翻转链表
    reverseLinkedList(node1);
    printf("%d   %d   %d\n",node1->value,node2->value,node3->value);
    return 0;
}