// На числовой прямой окрасили N отрезков.
// Известны координаты левого и правого концов каждого отрезка [Li, Ri]. Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
// N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 109].

// Формат ввода
// В первой строке записано количество отрезков.
// В каждой последующей строке через пробел записаны координаты левого и правого концов отрезка.

// Формат вывода
// Выведите целое число — длину окрашенной в один слой части.


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

template<typename T, typename Comparator = DefaultComparator<T>>
void MergeSort(T* arr, int len, Comparator comp = Comparator()) {
    if(len <= 1) {
        return;
    }
    int firstLen = len / 2;
    int secondLen = len - firstLen;
    MergeSort(arr, firstLen, comp);
    MergeSort(arr + firstLen, secondLen, comp);
    T* tmp = new T[len];
    Merge(arr, firstLen, arr + firstLen, secondLen, tmp, comp);
    copy(tmp, tmp + len, arr);
    delete[] tmp;
}
template<typename T, typename Comparator = DefaultComparator<T>>
void Merge(T* A, int lenA, T* B, int lenB, T* result, Comparator comp = Comparator()) {
    int topA = 0, topB = 0, topRes = 0;
    while(topA < lenA && topB < lenB) {
        if(comp(B[topB], A[topA])) {
            result[topRes] = B[topB];
            topRes += 1;
            topB += 1;
        } else {
            result[topRes] = A[topA];
            topRes += 1;
            topA += 1;
        }
    }
    while(topA < lenA) {
        result[topRes] =A[topA];
        topRes += 1;
        topA += 1;
    }
    while(topB < lenB) {
        result[topRes] = B[topB];
        topRes += 1;
        topB += 1;
    }
}

struct Point {
    int coord;
    bool isStart;

    Point() : coord(0), isStart(false) {};
    Point(int c, bool st) : coord(c), isStart(st) {};
    Point(const Point&) = default;
    Point(const Point&&) = delete;
    Point& operator=(const Point&) = default;
    Point& operator=(Point&&) = default;
    ~Point() = default;
    
    bool operator<(const Point& r) const {
        return coord < r.coord;
    }

};
int FindOneLayerLength(Point* pointArray, int len) {
    MergeSort(pointArray, len);
    int layers = 0;
    int length = 0;
    for(int i = 0; i < len; ++i) {
        if(layers == 1) {
            assert(i > 0);
            length += pointArray[i].coord - pointArray[i-1].coord;
        }
        if(pointArray[i].isStart) {
            layers += 1;
        } else {
            layers -= 1;
        }
    }
    return length;
}
int main() {
    int n = 0;
    cin >> n;
    Point* pointArray = new Point[2*n];
    int start = 0;
    int end = 0;  
    for(int i = 0; i < n; ++i) {
        cin >> start >> end;
        assert(i < n && 2*n - i - 1< 2*n);
        pointArray[i] = Point(start, true);
        pointArray[2*n -i -1] = Point(end, false);
    }
    int result = FindOneLayerLength(pointArray, 2*n);
    cout << result << endl;
    delete[] pointArray;
    return 0;
}