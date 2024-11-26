// Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
// Хранимые строки непустые и состоят из строчных латинских букв.
// Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера. 
// Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, 
// огда коэффициент заполнения таблицы достигает 3/4.
// Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и 
// проверки принадлежности данной строки множеству.

// Вариант 2. Для разрешения коллизий используйте двойное хеширование.

#include <iostream>
#include <cassert>
#include <vector>
#include <functional>

using namespace std;

template<typename T, typename HashFunc1, typename HashFunc2>
class StringSet {
private:
    struct entry {
        T value;
        bool isOccupied;
        bool isDeleted;

        entry(const entry&) = default;
        entry(const entry&&) = delete;
        entry& operator=(const entry&) = delete;
        entry& operator=(entry&&) = delete;
        ~entry() = default;

        entry() : isOccupied(false), isDeleted(false) {}
    };

    vector<entry> table;
    int size;
    int capacity;
    double loadFactor;

    HashFunc1 hash1;
    HashFunc2 hash2;

    void rehash() {
        int oldCapacity = capacity;
        capacity *= 2;
        vector<entry> oldTable = table;
        table = vector<entry>(capacity);

        size = 0;

        for (int i = 0; i < oldCapacity; ++i) {
            if (oldTable[i].isOccupied && !oldTable[i].isDeleted) {
                Add(oldTable[i].value);
            }
        }
    }

    int probe(const string& str, int i) const {
        return (hash1(str) + i * (2 * hash2(str) + 1)) % capacity;
    }

public:
    StringSet(HashFunc1 hashFunc1, HashFunc2 hashFunc2)
        : size(0), capacity(8), loadFactor(0.75), hash1(hashFunc1), hash2(hashFunc2) {
        table.resize(capacity);
    }

    void Add(const string& str) {
        if ((size + 1) > capacity * loadFactor) {
            rehash();
        }

        int i = 0;
        while (i < capacity) {
            int idx = probe(str, i);
            if (!table[idx].isOccupied || table[idx].isDeleted) {
                table[idx].value = str;
                table[idx].isOccupied = true;
                table[idx].isDeleted = false;
                ++size;
                return;
            }
            if (table[idx].value == str && !table[idx].isDeleted) {
                return; 
            }
            ++i;
        }
    }

    bool Contains(const string& str) const {
        int i = 0;
        while (i < capacity) {
            int idx = probe(str, i);
            if (table[idx].isOccupied && table[idx].value == str && !table[idx].isDeleted) {
                return true;
            }
            if (!table[idx].isOccupied) {
                return false;
            }
            ++i;
        }
        return false;
    }

    void Remove(const string& str) {
        int i = 0;
        while (i < capacity) {
            int idx = probe(str, i);
            if (table[idx].isOccupied && table[idx].value == str && !table[idx].isDeleted) {
                table[idx].isDeleted = true;
                --size;
                return;
            }
            if (!table[idx].isOccupied) {
                return;
            }
            ++i;
        }
    }
};

int main() {
    auto hash1 = [](const string& str) -> int {
        int hashValue = 0;
        for (char c : str) {
            hashValue = (hashValue * 31 + (c - 'a' + 1)) % (1 << 24);
        }
        return hashValue;
    };

    auto hash2 = [](const string& str) -> int {
        int hashValue = 0;
        for (char c : str) {
            hashValue = (hashValue * 37 + (c - 'a' + 1)) % (1 << 24);
        }
        return hashValue;
    };

    StringSet<string, decltype(hash1), decltype(hash2)> set(hash1, hash2);

    string operation, str;

    while (cin >> operation >> str) {
        if (operation == "+") {
            if (set.Contains(str)) {
                cout << "FAIL" << endl;
            } else {
                set.Add(str);
                cout << "OK" << endl;
            }

        } else if (operation == "-") {
            if (set.Contains(str)) {
                cout << "OK" << endl;
                set.Remove(str);
            } else {
                cout << "FAIL" << endl;
            }
        } else if (operation == "?") {
            if (set.Contains(str)) {
                cout << "OK" << endl;
            } else {
                cout << "FAIL" << endl;
            }
        }
    }
    return 0;
}
