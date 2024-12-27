// РК 3 ВАРИАНТ 2 ЗАДАЧА 2

// Нужно проверить, является ли неориентированный граф эйлеровым.

// Формат ввода
// Первая строка содержит число N – количество вершин.
// Вторая строка содержит число M - количество ребер.
// Каждая следующая строка содержит ребро (откуда, куда).

// Формат вывода
// 1 - если граф эйлеров
// 0 - если не эйлеров

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

void dfs(int node, const vector<vector<int>>& adj, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited);
        }
    }
}

bool isEulerian(int N, int M, vector<pair<int, int>>& edges) {
    if (M < N - 1) return false;  

    vector<vector<int>> adj(N);
    vector<int> degree(N, 0);  
    for (auto& edge : edges) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
        degree[edge.first]++;
        degree[edge.second]++;
    }

    for (int i = 0; i < N; ++i) {
        if (degree[i] % 2 != 0) {
            return false; 
        }
    }

    vector<bool> visited(N, false);
    dfs(0, adj, visited);

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

    if (isEulerian(N, M, edges)) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }

    return 0;
}
