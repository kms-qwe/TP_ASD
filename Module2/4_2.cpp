// 4_2. Порядковые статистики

// Дано число N и N строк. Каждая строка содержащит команду добавления или удаления натуральных чисел, 
// а также запрос на получение k-ой порядковой статистики. 
// Команда добавления числа A задается положительным числом A, 
// команда удаления числа A задается отрицательным числом “-A”. 
// Запрос на получение k-ой порядковой статистики задается числом k. 
// Требуемая скорость выполнения запроса - O(log n).

#include <iostream>
#include <algorithm>
#include <cassert>

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
class AVLTree {
private:

    struct Node {
        T key;
        int height;
        int size;
        Node* left;
        Node* right;

        explicit Node(const T& k) : key(k), left(nullptr), right(nullptr), height(1), size(1){}
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

    int height(Node* node) const {
        return node ? node->height : 0;
    }

    int size(Node* node) const {
        return node ? node->size : 0;
    }

    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + max(height(node->left), height(node->right));
            node->size = 1 + size(node->left) + size(node->right);
        }
    }

    int getBalance(Node* node) const {
        return node ? height(node->left) - height(node->right) : 0;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balance(Node* node) {
        updateHeight(node);
        int balanceFactor = getBalance(node);

        if (balanceFactor > 1) {
            if (getBalance(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }

        if (balanceFactor < -1) {
            if (getBalance(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    Node* Insert(Node* node, const T& key) {
        if (!node) {
            return new Node(key);
        }

        if (comp(key, node->key)) {
            node->left = Insert(node->left, key);
        } else if (comp(node->key, key)) {
            node->right = Insert(node->right, key);
        } else {
            return node; 
        }

        return balance(node);
    }

    Node* findMin(Node* node) const {
        return node->left ? findMin(node->left) : node;
    }

    Node* removeMin(Node* node) {
        if (!node->left) {
            return node->right;
        }
        node->left = removeMin(node->left);
        return balance(node);
    }

    Node* remove(Node* node, const T& key) {
        if (!node) {
            return nullptr;
        }

        if (comp(key, node->key)) {
            node->left = remove(node->left, key);
        } else if (comp(node->key, key)) {
            node->right = remove(node->right, key);
        } else {
            Node* left = node->left;
            Node* right = node->right;

            if (!right) {
                return left;
            }

            Node* minNode = findMin(right);
            minNode->right = removeMin(right);
            minNode->left = left;
            return balance(minNode);
        }

        return balance(node);
    }

    void inorder(Node* node) const {
        if (node) {
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
    }

    int kthOrderStatistic(Node* node, int k) {
        if (!node) return -1;  
        int leftSize = size(node->left);

        if (leftSize == k) return node->key;
        if (leftSize > k) {
            return kthOrderStatistic(node->left, k);  
        }
        return kthOrderStatistic(node->right, k - leftSize - 1);  
    }

public:
    AVLTree() : root(nullptr), comp(Comparator()) {}

    ~AVLTree() {
        delete root;
    }

    AVLTree(const AVLTree&) = delete;
    AVLTree(AVLTree&&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;
    AVLTree& operator=(AVLTree&&) = delete;

    void Insert(const T& key) {
        root = Insert(root, key);
    }

    void Remove(const T& key) {
        root = remove(root, key);
    }

    void PrintInOrder() const {
        inorder(root);
        cout << endl;
    }

    int KthOrderStatistic(int k) {
        assert(k >= 0 && size(root) >= k);
        return kthOrderStatistic(root, k);
    }
};


int main() {
    int n;
    cin >> n;
    AVLTree<int> tree;
    for (int i = 0; i < n; ++i) {
        int command = 0;
        int k = 0;
        cin >> command >> k;

        assert(command != 0);

        if (command > 0) {
            tree.Insert(command);
        } else {
            tree.Remove(-command);
        }

        cout << tree.KthOrderStatistic(k) << endl;
    }

        
    return 0;
}