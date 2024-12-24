#include "ListGraph.h"

ListGraph::ListGraph(int verticesCount) {
    adjacencyList.resize(verticesCount);
}

ListGraph::ListGraph(const IGraph& other) {
    int n = other.VerticesCount();
    adjacencyList.resize(n);
    for (int i = 0; i < n; ++i) {
        adjacencyList[i] = other.GetNextVertices(i);
    }
}

void ListGraph::AddEdge(int from, int to) {
    adjacencyList[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return adjacencyList.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    return adjacencyList[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev;
    for (int i = 0; i < adjacencyList.size(); ++i) {
        for (int v : adjacencyList[i]) {
            if (v == vertex) {
                prev.push_back(i);
            }
        }
    }
    return prev;
}
