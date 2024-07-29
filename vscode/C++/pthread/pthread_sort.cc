#include <iostream>
#include <random>
#include <vector>
#include"pthread_pool_2.h"

thread_pool pool;
void quickSort(std::vector<int> &arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }

        std::swap(arr[i + 1], arr[high]);
        int partitionIndex = i + 1;

        quickSort(arr, low, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, high);
    }
}


int main() 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 1000000); 
    const int num_random_numbers = 100000000;
    std::vector<int> random_numbers(num_random_numbers);
    for (int i = 0; i < num_random_numbers; ++i) 
        random_numbers[i] = dis(gen);

    
    quickSort(random_numbers,1,100000000);
    for (int i = 0; i < num_random_numbers; ++i) 
    std::cout << random_numbers[i] << " ";
    return 0;
}