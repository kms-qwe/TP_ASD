// РК 3 ВАРИАНТ 2 ЗАДАЧА 1

// Проверить, является ли неориентированный граф деревом.

// Формат ввода
// Первая строка содержит число N – количество вершин.
// Вторая строка содержит число M - количество ребер.
// Каждая следующая строка содержит ребро (откуда, куда).

// Формат вывода
// 1 - если граф дерево
// 0 - если не дерево

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

bool dfs(int node, int parent, const vector<vector<int>>& adj, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            if (!dfs(neighbor, node, adj, visited)) return false;
        } else if (neighbor != parent) {  
            return false;
        }
    }
    return true;
}

bool isTree(int N, int M, vector<pair<int, int>>& edges) {
    if (M != N - 1) return false; 
    
    vector<vector<int>> adj(N);
    for (auto& edge : edges) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }

    vector<bool> visited(N, false);
    
    if (!dfs(0, -1, adj, visited)) return false;

    for (bool v : visited) {
        if (!v) return false;
    }

    return true;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<pair<int, int>> edges(M);
    for (int i = 0; i < M; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }

    if (isTree(N, M, edges)) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }

    return 0;
}
