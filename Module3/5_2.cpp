// Дан неориентированный связный граф. 
// Требуется найти вес минимального остовного дерева в этом графе.

// Вариант 2. Для построения минимального остовного дерева используйте алгоритм Прима.
// Ваш номер варианта прописан в ведомости.
// Формат ввода
// Первая строка содержит два натуральных числа n и m — количество вершин и ребер графа соответственно 
// (1 ≤ n ≤ 20000, 0 ≤ m ≤ 100000).
// Следующие m строк содержат описание ребер по одному на строке.
// Ребро номер i описывается тремя натуральными числами bi, ei и wi — номера концов ребра и его вес соответственно 
// (1 ≤ bi, ei ≤ n, 0 ≤ wi ≤ 100000).

// Формат вывода
// Выведите единственное целое число - вес минимального остовного дерева.

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int to, weight;
    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};

long long findMstWeight(int n, const vector<vector<Edge>>& graph) {
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    vector<bool> inMst(n + 1, false);
    long long mstWeight = 0;

    pq.push({1, 0});
    
    while (!pq.empty()) {
        Edge current = pq.top();
        pq.pop();

        int v = current.to;
        int weight = current.weight;

        if (inMst[v]) continue;

        mstWeight += weight;
        inMst[v] = true;

        for (const auto& neighbor : graph[v]) {
            if (!inMst[neighbor.to]) {
                pq.push(neighbor);
            }
        }
    }

    return mstWeight;
}

int main() {
    int n, m;
    vector<vector<Edge>> graph;

    cin >> n >> m;
    graph.resize(n + 1); 

    for (int i = 0; i < m; i++) {
        int b, e, w;
        cin >> b >> e >> w;
        graph[b].push_back({e, w});
        graph[e].push_back({b, w});
    }

    long long mstWeight = findMstWeight(n, graph);

    cout << mstWeight << endl;

    return 0;
}
