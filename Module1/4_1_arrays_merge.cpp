// 4.1. Слияние массивов
// Ограничение времени	1 секунда
// Ограничение памяти	64Mb
// Ввод	стандартный ввод или input.txt
// Вывод	стандартный вывод или output.txt
// Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.

// Требования:

// Время работы O(N * logK)
// Куча должна быть реализована в виде шаблонного класса.
// Решение должно поддерживать передачу функции сравнения снаружи.
// Куча должна быть динамической.
// Формат ввода
// Сначала вводится количество массивов K.
// . Затем по очереди размер каждого массива и элементы массива.
// Каждый массив упорядочен по возрастанию.

// Формат вывода
// Итоговый отсортированный массив.

#include <iostream>
#include <cassert>

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

int HEAP_INIT_SIZE = 2;
template<typename T, typename Comparator = DefaultComparator<T>>
class Heap {
public:
    Heap(const Heap&) = delete;
    Heap(const Heap &&) = delete;
    Heap& operator=(const Heap &) = delete;
    Heap& operator=(Heap &&) = delete;

    Heap(): size(HEAP_INIT_SIZE), count(0), comp(Comparator()) {
        data = new T[HEAP_INIT_SIZE];
    }; 

    ~Heap() {
        delete[] data;
    };

    const T& Top() const {
        assert(not Empty());
        return data[0];
    };
    void Pop() {
        assert(not Empty());
        data[0] = data[count - 1];
        data[count - 1] = T{};
        count -= 1;
        
        siftDown(0);
    };
    void Push(const T& newElement) {
        if(count == size) {
            grow();
        }
        data[count] = newElement;
        count += 1;
        siftUp(count - 1);

    };
    bool Empty() const {
        return count == 0;
    }
    // void Print() const {
    //     cout << "HEAP | size = " << size << " | count = " << count << endl;
    //     for(int i = 0; i < size; ++i) {
    //         data[i].Print();
    //     }
    // }
private:
    T* data;
    int size;
    int count;
    Comparator comp;
    void siftUp(int index) {
        while( index > 0) {
            int parent = (index - 1) / 2;
            if(comp(data[index], data[parent])) {
                return ;
            }
            swap(data[index], data[parent]);
            index = parent;
        }
    };
    void siftDown(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        if(left < count && comp(data[i], data[left])) {
            largest = left;
        }
        if(right< count && comp(data[largest], data[right])) {
            largest = right;
        }
        if(largest != i) {
            swap(data[i], data[largest]);
            siftDown(largest);
        }
    };
    void grow() {
        assert(count == size);
        size *= 2;
        T* newData = new T[size];
        copy(data, data + count, newData);
        delete[] data;
        data = newData;
    };
    
};

struct Descriptor {
    int* arr;
    int len;
    int bottom;

    Descriptor() : arr(nullptr), len(0), bottom(0) {} ;
    Descriptor(const Descriptor&) = delete;
   
    Descriptor& operator=(const Descriptor& other) {
        if(this != &other) {
            len = other.len;
            bottom = other.bottom;
            delete[] arr;
            arr = new int[len];
            copy(other.arr, other.arr + len, arr);
        }
        return *this;
    };
    Descriptor(Descriptor&& other): arr(other.arr), len(other.len), bottom(other.bottom) {
        other.arr = nullptr;
    };
    Descriptor& operator=(Descriptor&& other) {
        if(this != &other) {
            delete[] arr;
            arr = other.arr;
            len = other.len;
            bottom = other.bottom;

            other.arr = nullptr;
        }
        return *this;
    };
   
    Descriptor(int* array, int size): len(size), bottom(0) {
        arr = new int[len];
        copy(array, array + size, arr);
    };
    ~Descriptor() {
        delete[] arr;
    };
    bool operator<(const Descriptor& r) const {
        assert(bottom < len && r.bottom < r.len && len > 0 && r.len > 0);
        return arr[bottom] > r.arr[r.bottom];
    };
    // void Print() const{
    //     cout << "DESCRIPTOR | len = " << len << " | bottom = " << bottom << endl;
    //     for(int i = 0 ; i < len; ++i) {
    //         cout << arr[i] << " ";
    //     } 
    //     cout << endl;
    // }
};
void MergeSortArray(Heap<Descriptor>& ArrayHeap, int* mergeResult) {
    Descriptor minDesc;
    int bottomResult = 0;
    while(not ArrayHeap.Empty()) {
        minDesc = ArrayHeap.Top();
        ArrayHeap.Pop();
        mergeResult[bottomResult] = minDesc.arr[minDesc.bottom];
        minDesc.bottom += 1;
        bottomResult += 1;
        if(minDesc.bottom < minDesc.len) {
             ArrayHeap.Push(move(minDesc));
        }     
    }  
}
int main() {
    int k = 0, n = 0;
    cin >> k;
    Heap<Descriptor> ArrayHeap;
    for(int i = 0; i < k; ++i) {
        int size = 0;
        cin >> size;
        if(size == 0) {
            continue;
        }
        n += size;
        int* array = new int[size];
        for(int j = 0; j < size; ++j) {
            cin >> array[j];
        }
        
        Descriptor desc(array, size);
        ArrayHeap.Push(move(desc));

        delete[] array;
    }

    int* mergeResult = new int[n];
    MergeSortArray(ArrayHeap, mergeResult);
    for(int i = 0; i < n; ++i) {
        cout << mergeResult[i] << " ";
    }
    cout << endl;
    
    delete[] mergeResult;
    return 0;
}