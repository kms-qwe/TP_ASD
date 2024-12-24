#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int verticesCount) {
    adjacencyMatrix.resize(verticesCount, std::vector<int>(verticesCount, 0));
}

MatrixGraph::MatrixGraph(const IGraph& other) {
    int n = other.VerticesCount();
    adjacencyMatrix.resize(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int to : other.GetNextVertices(i)) {
            adjacencyMatrix[i][to] = 1;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    adjacencyMatrix[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
    return adjacencyMatrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> nextVertices;
    for (int i = 0; i < adjacencyMatrix[vertex].size(); ++i) {
        if (adjacencyMatrix[vertex][i] == 1) {
            nextVertices.push_back(i);
        }
    }
    return nextVertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prevVertices;
    for (int i = 0; i < adjacencyMatrix.size(); ++i) {
        if (adjacencyMatrix[i][vertex] == 1) {
            prevVertices.push_back(i);
        }
    }
    return prevVertices;
}
