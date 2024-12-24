#include "SetGraph.h"

SetGraph::SetGraph(int verticesCount) {
    adjacencySets.resize(verticesCount);
}

SetGraph::SetGraph(const IGraph& other) {
    int n = other.VerticesCount();
    adjacencySets.resize(n);
    for (int i = 0; i < n; ++i) {
        for (int to : other.GetNextVertices(i)) {
            adjacencySets[i].insert(to);
        }
    }
}

void SetGraph::AddEdge(int from, int to) {
    adjacencySets[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return adjacencySets.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    return std::vector<int>(adjacencySets[vertex].begin(), adjacencySets[vertex].end());
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev;
    for (int i = 0; i < adjacencySets.size(); ++i) {
        if (adjacencySets[i].count(vertex)) {
            prev.push_back(i);
        }
    }
    return prev;
}
