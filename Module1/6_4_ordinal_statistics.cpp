// Дано множество целых чисел из [0..109] размера n.

// Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:

// 10% перцентиль
// медиана
// 90% перцентиль
// Требования:

// К дополнительной памяти: O(n).
// Среднее время работы: O(n)
// Должна быть отдельно выделенная функция partition.
// Рекурсия запрещена.
// Решение должно поддерживать передачу функции сравнения снаружи.
// Формат ввода
// Сначала вводится кол-во элементов массива n. После сам массив.

// Формат вывода
// Параметры множества в порядке:

// 10% перцентиль
// медиана
// 90% перцентиль


// 6_4. Реализуйте стратегию выбора опорного элемента “случайный элемент”. 
// Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.

#include <iostream>
#include <cassert>
#include <random>

using namespace std;

template<typename T>
struct DefaultComparator {
    DefaultComparator() = default;
    DefaultComparator(const DefaultComparator&) = default;
    DefaultComparator(const DefaultComparator&&) = delete;
    DefaultComparator& operator=(const DefaultComparator&) = delete;
    DefaultComparator& operator=(DefaultComparator&&) = delete;
    ~DefaultComparator() = default;
    bool operator()(const T& l, const T& r) const {
        return l < r;
    }
};

int GetRandomInt(int l, int r) {
    assert(l < r); 

    random_device rd;  
    mt19937 gen(rd()); 
    uniform_int_distribution<> dist(l, r - 1); 

    return dist(gen);
}

template<typename T, typename Comparator = DefaultComparator<T>>
int Partition(T* arr, int l, int r, Comparator comp = Comparator()) {
    assert(l < r);

    int pivotInd = GetRandomInt(l, r);
    std::swap(arr[pivotInd], arr[r - 1]);
    T& pivot = arr[r - 1];

    int i = r - 2;
    int j = r - 2;

    while (j >= l) {
        if (!comp(arr[j], pivot)) {
            std::swap(arr[i], arr[j]);
            i--;
        }
        j--;
    }

    std::swap(arr[i + 1], arr[r - 1]);

    return i + 1; 
}

template<typename T, typename Comparator = DefaultComparator<T>>
void KthEelement(T* arr, int size, int k, Comparator comp = Comparator()) {
    int l = 0, r = size; 
    
    while(l < r) {
        int pivotPos = Partition(arr, l, r, comp);
        if (pivotPos == k) {
            return;
        }

        if(k < pivotPos) {
            r = pivotPos;
        } else {
            l = pivotPos + 1;
        }
    }
}


int main() {
    int size = 0;
    cin >> size;
    int* arr = new int[size];
    for(int i = 0; i < size; ++i) {
        cin >> arr[i];
    }

    int percentile10 = size * 1 / 10;
    int median = size / 2;
    int percentile90 = size * 9 / 10;
   
    KthEelement(arr, size, percentile10);
    cout << arr[percentile10] << endl;

    KthEelement(arr, size, median);
    cout << arr[median] << endl;

    KthEelement(arr, size, percentile90);
    cout << arr[percentile90] << endl;

    delete[] arr;
    return 0;
}