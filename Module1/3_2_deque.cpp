// 3.2. Дек с динамическим буфером
// Ограничение времени	1 секунда
// Ограничение памяти	10Mb
// Ввод	стандартный ввод или input.txt
// Вывод	стандартный вывод или output.txt
// Реализовать дек с динамическим зацикленным буфером.

// Обрабатывать команды push * и pop *.

// Формат ввода
// В первой строке количество команд n. n ≤ 1000000.

// Каждая команда задаётся как 2 целых числа: a b.

// a = 1 - push front
// a = 2 - pop front
// a = 3 - push back
// a = 4 - pop back

// Если дана команда pop *, то число b - ожидаемое значение. Если команда pop * вызвана для пустой структуры данных, то ожидается “-1”.

#include <iostream>
#include <cassert>

using namespace std;
const int INIT_DEQUE_SIZE = 8;
template<typename T>
class Deque {
private:
    T* data;
    int size;
    int head;
    int tail;
    int count; 
    void increaseSize() {
        assert(count == size);
        T* newData = new T[2*size];
        for(int i = 0; i < size; ++i) {
            newData[i] = data[(head + i) % size];
        }
        head = 0;
        tail = size - 1;
        size *= 2;

        delete[] data;
        data = newData;
    }
public:
    Deque(const Deque&) = delete;
    Deque(const Deque&&) = delete;
    Deque& operator=(Deque &&) = delete;
    
    Deque(): size(INIT_DEQUE_SIZE), head(0), tail(0), count(0) {
        data =  new T[size];
    }
    ~Deque() {
        delete[] data;
    }
    Deque& operator=(const Deque& other) {
        if (this != &other) {
            size = other.size;
            head = other.head;
            tail = other.tail;
            count = other.count;

            T* newData = new T[size];
            for(int i = 0; i < size; ++i) {
                newData[i] = other.data[i];
            }
            delete[] data;
            data = newData;
        }
        return *this;
    }

    void PushFront(const T& newElement) {
        if (Empty()) {
            data[head] = newElement;
            count += 1;
            return ;
        }
        if (count == size) {
            increaseSize();
        }
        head = (head - 1 + size) % size;
        data[head] = newElement;
        count += 1;
    }

    void PushBack(const T& newElement) {
        if (Empty()) {
            data[tail] = newElement;
            count += 1;
            return ;
        }

        if (count == size) {
            increaseSize();
        }
        tail = (tail + 1) % size;
        data[tail] = newElement;
        count += 1;

    }

    T PopFront() {
        assert(not Empty());
        T value = data[head];
        data[head] = T(0);
        if (count == 1) {
            count -= 1;
            return value;
        }
        head = (head + 1) % size;
        count -= 1;
        return value;
    }

    T PopBack() {
        assert(not Empty());
        T value = data[tail];
        data[tail] = T(0);
        if (count == 1) {
            count -= 1;
            return value;
        }
        tail = (tail - 1 + size) % size;
        count -= 1;
        return value;
    }

    bool Empty() {
        return count == 0;
    }
    
    void Print() {
        cout << "START DEQUE | size = " << size << " | head = " << head << " | tail = " << tail << " | count = " << count << endl;
        for(int i = 0; i < size; ++i) {
            cout << "data[" << i << "] = " << data[i] << endl;;
        }
        cout << "END DEQUE" << endl;
    }
};

int main() {
    int n = 0;
    int command = 0;
    int value = 0;
    cin >> n;
    Deque<int> deque = Deque<int>();
    for(int i = 0; i < n; ++i) {
        cin >> command >> value;
        if(command == 1) {
            deque.PushFront(value);
        } else if(command == 2) {
            int popValue = deque.Empty() ? -1 : deque.PopFront();
            if (value != popValue) {
                cout << "NO" << endl;
                return 0;
            }
        } else if(command == 3) {
            deque.PushBack(value);
        } else if(command == 4) {
            int popValue = deque.Empty() ? -1 : deque.PopBack();
            if( value != popValue) {
                cout << "NO" << endl;
                return 0;
            }
        } else {
            cout << "Invalid command" << endl;
            return 0;
        }
    }

    cout << "YES" << endl;
    return 0;
}