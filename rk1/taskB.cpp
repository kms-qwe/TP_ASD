#include <iostream>
#include <string>
#include <cassert>

using namespace std;

template<typename T>
class Stack {
private:
    T* arr;         
    int top;  
    int capacity;  

public:
    Stack(int size) {
        capacity = size;
        arr = new T[capacity]; 
        top = -1;
    }

    ~Stack() {
        delete[] arr; 
    }

    Stack(const Stack& other) = delete;
    Stack& operator=(const Stack& other) = delete;
    Stack(Stack&& other) = delete;
    Stack& operator=(Stack&& other) = delete;

    void push(T element) {
        assert(top < capacity -1);
        arr[++top] = element; 
    }

    T pop() {
        assert(not isEmpty());
        return arr[top--]; 
    }

    T peek() const { 
        assert(not isEmpty());
        return arr[top];
    }

    bool isEmpty() const {
        return top == -1; 
    }
};

bool isStackAnagram(const string& source, const string& target) {
    assert(source.length() == target.length());


    Stack<char> stack(source.length());
    int pointer = 0; 
    for(int i = 0; i <  source.length(); ++i) {
        stack.push(source[i]);

        while (!stack.isEmpty() && stack.peek() == target[pointer]) {
            stack.pop();
            pointer++;
        }
    }


    return pointer == target.length();
}

int main() {
    string source, target;
    cin >> source >> target; 

    if(isStackAnagram(source, target)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
