// 7.2. LSD для long long

// Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 1000000. 
// Отсортировать массив методом поразрядной сортировки LSD по байтам.

#include <iostream>
#include <cassert>

using namespace std;

template<typename T, typename KeyFunc>
void CountSort(T* arr, int size, const int alphaSize, KeyFunc key) {
    int* counters = new int[alphaSize];
    fill(counters, counters + alphaSize, 0);

    for(int i = 0; i < size; ++i) {
        counters[key(arr[i])] += 1;
    }

    for(int i = 0; i < alphaSize - 1; ++i) {
        counters[i + 1] += counters[i];
    }

    T* tmp = new T[size];
    for(int i = size - 1; i >= 0; --i) {
        size_t k = key(arr[i]);
        counters[k] -= 1;
        size_t countersIndex = counters[k];
        tmp[countersIndex] = arr[i];
    }

    copy(tmp, tmp + size, arr);

    delete[] tmp;
    delete[] counters;
}

size_t GetByte(const long long& num, int byteIndex) {
    return (num >> (byteIndex * 8)) & 0xFF;
}

void LSD(long long* arr, int size) {
    const int BYTE_SIZE = 256; 
    const int NUM_PASSES = 8;  
    for (int byteIndex = 0; byteIndex < NUM_PASSES; ++byteIndex) {
        CountSort(arr, size, BYTE_SIZE, [byteIndex](const long long &num) {
            return GetByte(num, byteIndex);
        });
    }
}


int main() {
    int size = 0;
    cin >> size;
    long long* arr = new long long[size];
    for(int i = 0; i < size; ++i) {
        cin >> arr[i];
    }

    LSD(arr, size);
    
    for(int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;
    return 0;
}