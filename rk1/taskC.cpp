#include <iostream>
#include <cassert>

using namespace std;

struct Box {
    int width;
    int height;
    int depth;
    int index;

    Box(int w, int h, int d, int idx) : width(w), height(h), depth(d), index(idx) {}

    ~Box() = default;
    Box() = default;
    Box(const Box&) = default;
    Box& operator=(const Box&) = default;
};

void insertionSort(Box* boxes, int n) {
    for (int i = 1; i < n; i++) {
        Box key = boxes[i];
        int j = i - 1;

        while (j >= 0 && (boxes[j].width > key.width || 
                          (boxes[j].width == key.width && boxes[j].height > key.height) || 
                          (boxes[j].width == key.width && boxes[j].height == key.height && boxes[j].depth > key.depth))) {
            boxes[j + 1] = boxes[j];
            boxes[j + 1].index = boxes[j].index;
            j--;
        }
        boxes[j + 1] = key;
        boxes[j+1].index = key.index;
    }
}


int main() {
    int n;
    cin >> n;

    Box* boxes = new Box[n];

    for (int i = 0; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        boxes[i] = Box(x, y, z, i);
    }

    insertionSort(boxes, n);
    for(int i = 0; i < n; ++i) {
        cout << boxes[i].index << " ";
    }
    cout << endl;
    delete[] boxes;
    return 0;
}
