// Задача 3. B-дерево (4 балла)

// Постройте B-дерево минимального порядка t и выведите его по слоям.
// В качестве ключа используются числа, лежащие в диапазоне 0..232 -1

// Требования: 
// B-дерево должно быть реализовано в виде шаблонного класса.
// Решение должно поддерживать передачу функции сравнения снаружи.

// Формат входных данных
// Сначала вводится минимальный порядок дерева t.
// Затем вводятся элементы дерева.

// Формат выходных данных
// Программа должна вывести B-дерево по слоям. 
// Каждый слой на новой строке, элементы должны выводится в том порядке, в котором они лежат в узлах.


#include <iostream>
#include <vector>
#include <queue>
#include <functional>

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
class BTree {
private:
    struct Node {
        std::vector<T> keys;           
        std::vector<Node*> children;   
        bool isLeaf;                   

        explicit Node(bool leaf) : isLeaf(leaf) {}
    };

    Node* root;
    int t;                  
    Comparator comp;

    void insertNonFull(Node* node, const T& key) {
        int i = static_cast<int>(node->keys.size()) - 1;

        if (node->isLeaf) {
            node->keys.push_back(T());
            while (i >= 0 && comp(key, node->keys[i])) {
                node->keys[i + 1] = node->keys[i];
                --i;
            }
            node->keys[i + 1] = key;
        } else {
            while (i >= 0 && comp(key, node->keys[i])) {
                --i;
            }
            ++i;

            if (static_cast<int>(node->children[i]->keys.size()) == 2 * t - 1) {
                splitChild(node, i);

                if (comp(node->keys[i], key)) {
                    ++i;
                }
            }
            insertNonFull(node->children[i], key);
        }
    }

    void splitChild(Node* parent, int index) {
        Node* fullChild = parent->children[index];
        Node* newChild = new Node(fullChild->isLeaf);

        for (int j = 0; j < t - 1; ++j) {
            newChild->keys.push_back(fullChild->keys[j + t]);
        }

        if (!fullChild->isLeaf) {
            for (int j = 0; j < t; ++j) {
                newChild->children.push_back(fullChild->children[j + t]);
            }
        }

        fullChild->keys.resize(t - 1);
        fullChild->children.resize(fullChild->isLeaf ? 0 : t);

        parent->children.insert(parent->children.begin() + index + 1, newChild);
        parent->keys.insert(parent->keys.begin() + index, fullChild->keys[t - 1]);
    }

    void printByLevels(Node* node) const {
        if (!node) return;

        std::queue<Node*> q;
        q.push(node);

        while (!q.empty()) {
            int levelSize = static_cast<int>(q.size());
            for (int i = 0; i < levelSize; ++i) {
                Node* current = q.front();
                q.pop();

                for (const T& key : current->keys) {
                    std::cout << key << " ";
                }

                if (!current->isLeaf) {
                    for (Node* child : current->children) {
                        q.push(child);
                    }
                }
            }
            std::cout << "\n";
        }
    }

    void deleteTree(Node* node) {
        if (!node) return;

        if (!node->isLeaf) {
            for (Node* child : node->children) {
                deleteTree(child);
            }
        }
        delete node;
    }

public:
    explicit BTree(int t, Comparator cmp = Comparator())
        : root(nullptr), t(t), comp(cmp) {}

    ~BTree() {
        deleteTree(root);
    }

    void Insert(const T& key) {
        if (!root) {
            root = new Node(true);
            root->keys.push_back(key);
            return;
        }

        if (static_cast<int>(root->keys.size()) == 2 * t - 1) {
            Node* newRoot = new Node(false);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0);

            int i = comp(key, newRoot->keys[0]) ? 0 : 1;
            insertNonFull(newRoot->children[i], key);

            root = newRoot;
        } else {
            insertNonFull(root, key);
        }
    }

    void PrintTree() const {
        printByLevels(root);
    }
};


int main() {
    int t;
    std::cin >> t;

    BTree<int> btree(t);

    int key;
    while (std::cin >> key) {
        btree.Insert(key);
    }

    btree.PrintTree();
    return 0;
}
