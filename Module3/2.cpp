// Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами. 
// Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).

// Формат ввода
// v: кол-во вершин (макс. 50000),
// n: кол-во ребер(макс. 200000),
// n пар реберных вершин,
// пара вершин (u, w) для запроса.

// Формат вывода
// Количество кратчайших путей от v к w.

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cassert>
using namespace std;

int countShortestPaths(int v, int n, vector<pair<int, int>>& edges, int u, int w) {
    vector<vector<int>> graph(v);

    for (auto& edge : edges) {
        graph[edge.first].push_back(edge.second);
        graph[edge.second].push_back(edge.first);
    }

    vector<int> distance(v, INT_MAX); 
    vector<int> ways(v, 0);           
    queue<int> q;
    q.push(u);
    distance[u] = 0;
    ways[u] = 1;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : graph[current]) {
            if (distance[neighbor] > distance[current] + 1) {
                distance[neighbor] = distance[current] + 1;
                ways[neighbor] = ways[current];
                q.push(neighbor);
            } else if (distance[neighbor] == distance[current] + 1) {
                ways[neighbor] += ways[current];
            }
        }
    }

    return ways[w];
}

int main() {
    int v, n;
    cin >> v >> n;
    assert(v >= 0 && n >= 0);
    vector<pair<int, int>> edges(n);
    for (int i = 0; i < n; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }

    int u, w;
    cin >> u >> w;

    cout << countShortestPaths(v, n, edges, u, w) << endl;

    return 0;
}
