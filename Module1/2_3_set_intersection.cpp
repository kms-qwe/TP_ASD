// 2.3. Пересечение множеств
// Ограничение времени	0.05 секунд
// Ограничение памяти	4Mb
// Ввод	стандартный ввод или input.txt
// Вывод	стандартный вывод или output.txt
// Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию. A[0..n-1] и B[0..m-1]. n » m. 
// Найдите их пересечение. Требуемое время работы: O(m * log k), где k - позиция элементта B[m-1] в массиве A. 
// В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1]. n, k ≤ 10000.

#include <iostream>
#include <cassert>

using namespace std;

int exponentialSearch(int searched, int n, int* A) {
    if (n == 0 || A[n-1] < searched) {
        return -1;
    } 

    int right = 1;
    while(right < n && A[right] < searched) {
        right *= 2;
    }
    int left = right / 2;
    right = right > n ? n -1 : right;
    int med = (right + left) / 2;

    while(left <= right) {
        if (A[med] == searched) {
            return med;
        }
        if (A[med] < searched) {
            left = med + 1;
        } else {
            right = med - 1;
        }
        med = (left + right) / 2;
    }

    return -1;
}
int findIntersection(int n, int m, int* A, int* B, int* result) {
    int resultlen = 0;
    for(int i = 0; i < m; ++i){

        if(exponentialSearch(B[i], n, A) != -1) {
            result[resultlen] = B[i];
            resultlen += 1;
        }
    }
    return resultlen;

}
int main() {
    int n = 0, m = 0;
    cin >> n >> m;
    int* A = new int[n];
    for(int i = 0; i < n; ++i) {
        cin >> A[i];
    }
    int* B = new int[m];
    for(int i = 0; i < m; ++i) {
        cin >> B[i];
    }

    int* arraysIntersection = new int[m];
    int lenOfIntersection = findIntersection(n, m, A, B, arraysIntersection);
    for(int i = 0; i < lenOfIntersection; ++i){
        cout << arraysIntersection[i] << " ";
    }
    cout << endl;

    delete[] A;
    delete[] B;
    delete[] arraysIntersection;
    return 0;
}