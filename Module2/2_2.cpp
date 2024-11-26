// Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
// Требуется построить бинарное дерево, заданное наивным порядком вставки.
// Т.е., при добавлении очередного числа K в дерево с корнем root, 
// если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
// Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
// 2_2. Выведите элементы в порядке pre-order (сверху вниз).

#include <iostream>
#include <vector>
#include <functional>
#include <stack>

using namespace std;

template <typename T>
struct DefaultComparator {
    DefaultComparator() = default;
    DefaultComparator(const DefaultComparator&) = default;
    DefaultComparator(DefaultComparator&&) = default;
    DefaultComparator& operator=(const DefaultComparator&) = default;
    DefaultComparator& operator=(DefaultComparator&&) = default;
    ~DefaultComparator() = default;

    bool operator()(const T& l, const T& r) const {
        return l < r; 
    }
};

template <typename T, typename Comparator = DefaultComparator<T>>
class BinaryTree {
private:
    struct Node {
        T key;
        Node* left;
        Node* right;

        explicit Node(const T& k) : key(k), left(nullptr), right(nullptr) {}
        Node(const Node&) = delete;
        Node(Node&&) = delete;
        Node& operator=(const Node&) = delete;
        Node& operator=(Node&&) = delete;

        ~Node() {
            delete left;
            delete right;
        }
    };

    Node* root;
    Comparator comp;

    BinaryTree(const BinaryTree&) = delete;
    BinaryTree(BinaryTree&&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;
    BinaryTree& operator=(BinaryTree&&) = delete;

public:
    explicit BinaryTree(Comparator cmp = Comparator()) : root(nullptr), comp(cmp) {}

    ~BinaryTree() {
        delete root;
    }

    void Insert(const T& key) {
        if (!root) {
            root = new Node(key);
            return;
        }
        Node* current = root;
        while (true) {
            if (comp(key, current->key)) { 
                if (current->left) {
                    current = current->left;
                } else {
                    current->left = new Node(key);
                    break;
                }
            } else { 
                if (current->right) {
                    current = current->right;
                } else {
                    current->right = new Node(key);
                    break;
                }
            }
        }
    }

    void PreOrderTraversal(const function<void(const T&)>& action) {
        if (!root) return;

        stack<Node*> stack;
        stack.push(root);

        while (!stack.empty()) {
            Node* current = stack.top();
            stack.pop();

            action(current->key);

            if (current->right) stack.push(current->right);
            if (current->left) stack.push(current->left);
        }
    }
};

int main() {
    int N;
    cin >> N;

    BinaryTree<int> tree;

    for (int i = 0; i < N; ++i) {
        int value;
        cin >> value;
        tree.Insert(value);
    }

    tree.PreOrderTraversal([](const int& key) {
        cout << key << " ";
    });
    cout << endl;

    return 0;
}
