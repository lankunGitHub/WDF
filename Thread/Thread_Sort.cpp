#include<thread>
#include<iostream>
#include<mutex>
#include<condition_variable>
#include<vector>
#include<chrono>
#include<array>
#include<ctime>
#include<cstdlib>

#define THREAD_NUM 16

int partition(std::array<int,100000> &arr,int start,int end)
{
    int pivot = arr[start + (end - start) / 2];
    int i = start;
    int j = end;

    while (i <= j) {
        while (arr[i] < pivot) 
            i++;
        while (arr[j] > pivot) 
            j--;
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    return i;
}
void thread_merge(std::array<int,100000> &arr,int start,int end,int mid)
{
    std::array<int,100000> temp;
    int i = start;
    int j = mid + 1;
    int k = 0;
    while (i <= mid && j <= end) 
    {
        if(arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= mid) 
        temp[k++] = arr[i++];
    while (j <= end) 
        temp[k++] = arr[j++];
    for (int m = 0; m < k; m++) 
        arr[start + m] = temp[m];
}
void thread_sort(std::array<int, 100000> &arr, int start, int end)
{
    if(start < end)
    {
        int mid = partition(arr, start, end);
        std::thread thread1(thread_sort,arr,start,mid);
        std::thread thread2(thread_sort,arr,mid+1,end);
        thread_merge(arr, start, end, mid);
        thread1.join();
        thread2.join();
    }
    return;
}
int main() 
{
    auto start = std::chrono::high_resolution_clock::now();
    srand(time(NULL));
    std::array<int, 100000> sort_array;
    for (int i = 0; i < 100000; i++)
        sort_array[i] = rand() % 1000;
    std::chrono::duration<double> duration = end - start;
    std::cout << "程序运行时间： " << duration.count() << " 秒" << std::endl;

    return 0;
}