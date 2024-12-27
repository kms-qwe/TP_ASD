#include "graph.h"
#include <queue>
#include <numeric> 
#include <algorithm> 

Graph::Graph(int n, const std::vector<Point>& points) : n(n), adjList(n + 1) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double dist = Point::distance(points[i], points[j]);
            adjList[i + 1].push_back({j + 1, dist});
            adjList[j + 1].push_back({i + 1, dist});
        }
    }
}

void Graph::preorderTraversal(int v, const std::vector<std::vector<int>>& mstAdjList, 
                          std::vector<bool>& visited, std::vector<int>& path) {
        visited[v] = true;
        path.push_back(v);

        for (int u : mstAdjList[v]) {
            if (!visited[u]) {
                preorderTraversal(u, mstAdjList, visited, path);
            }
        }
    }
std::pair<double, std::vector<int>> Graph::findTspPath() {
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
    std::vector<bool> inMst(n + 1, false);
    std::vector<std::vector<int>> mstAdjList(n + 1);
    long long mstWeight = 0;

    pq.push({1, 0});
    while (!pq.empty()) {
        Edge current = pq.top();
        pq.pop();

        int v = current.to;
        double weight = current.weight;

        if (inMst[v]) continue;

        mstWeight += weight;
        inMst[v] = true;

        for (const auto& neighbor : adjList[v]) {
            if (!inMst[neighbor.to]) {
                pq.push(neighbor);
                mstAdjList[v].push_back(neighbor.to);
                mstAdjList[neighbor.to].push_back(v);
            }
        }
    }

    std::vector<bool> visited(n + 1, false);
    std::vector<int> path;
    preorderTraversal(1, mstAdjList, visited, path);
    
    path.push_back(1);

    double tspWeight = 0;
    for (size_t i = 1; i < path.size(); ++i) {
        for (const auto& edge : adjList[path[i-1]]) {
            if (edge.to == path[i]) {
                tspWeight += edge.weight;
                break;
            }
        }
    }
    
    return {tspWeight, path};
}

const std::vector<std::vector<Edge>>& Graph::getAdjList() const {
    return adjList;
}


double Graph::exactTSP(const std::vector<Point>& points) {
    int n = points.size();
    std::vector<int> nodes(n);
    std::iota(nodes.begin(), nodes.end(), 0); 

    double minDistance = std::numeric_limits<double>::infinity();

    do {
        double currentDistance = 0.0;
        for (int i = 1; i < n; ++i) {
            currentDistance += Point::distance(points[nodes[i - 1]], points[nodes[i]]);
        }
        currentDistance += Point::distance(points[nodes[n - 1]], points[nodes[0]]);

        minDistance = std::min(minDistance, currentDistance);

    } while (std::next_permutation(nodes.begin(), nodes.end()));  

    return minDistance;
}