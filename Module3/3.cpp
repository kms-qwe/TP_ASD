// Требуется отыскать самый короткий маршрут между городами. 
// Из города может выходить дорога, которая возвращается в этот же город.

// Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.

// Формат ввода
// Первая строка содержит число N – количество городов, 3 ≤ N ≤ 10000.

// Вторая строка содержит число M - количество дорог, 1 ≤ M ≤ 250000.

// Каждая следующая строка содержит три числа u, v, w – описание дороги: откуда, куда, время в пути. 
// 0 ≤ u < N, 0 ≤ v < N, 1 ≤ w ≤ 10000. Между любыми двумя городами может быть больше одной дороги.

// Последняя строка содержит два числа: s и t – маршрут (откуда и куда нужно доехать). 0 ≤ s < N, 0 ≤ t < N.

// Формат вывода
// Вывести длину самого короткого маршрута.

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cassert>

using namespace std;

const int INF = numeric_limits<int>::max();

typedef pair<int, int> Edge; 

double findShortestPath(int n, int m, vector<vector<Edge>>& graph, int s, int t) {
    vector<int> distance(n, INF);
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    distance[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        int current_dist = pq.top().first;
        int current_city = pq.top().second;
        pq.pop();

        if (current_dist > distance[current_city]) {
            continue;
        }

        for (auto& edge : graph[current_city]) {
            int weight = edge.first;
            int neighbor = edge.second;

            if (distance[current_city] + weight < distance[neighbor]) {
                distance[neighbor] = distance[current_city] + weight;
                pq.push({distance[neighbor], neighbor});
            }
        }
    }

    return distance[t];
}

int main() {
    int n, m;
    cin >> n >> m;
    // assert(3 <= n && n <= 10000 && 1 <= m && m <= 250000);

    vector<vector<Edge>> graph(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        // assert(0 <= u && u < n && 0 <= v && v < n && 1 <= w && w <= 100000);
        graph[u].push_back({w, v});
        graph[v].push_back({w, u});
    }

    int s, t;
    cin >> s >> t;

    int result = findShortestPath(n, m, graph, s, t);
    // assert(result != INF);
    if (result == INF) {
        cout << -1 << endl;
    } else {
        cout << result << endl;

    }   

    return 0;
}
