#include <iostream>

using namespace std;

int binsearch(int* A, int n, int k) {
    int left = 0, right = n;

    while (left < right) {
        int mid = (left + right) / 2;
        if (A[mid] < k) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left; 
}

int main() {
    int n;
    cin >> n; 
    int* A = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> A[i]; 
    }
    int k;
    cin >> k;
    int position = binsearch(A, n, k);
    cout << position << endl;
    delete[] A;
    return 0;
}
