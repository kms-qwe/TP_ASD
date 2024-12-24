#include "ArcGraph.h"

ArcGraph::ArcGraph(int verticesCount) : verticesCount(verticesCount) {}

ArcGraph::ArcGraph(const IGraph& other) {
    verticesCount = other.VerticesCount();
    for (int i = 0; i < verticesCount; ++i) {
        for (int to : other.GetNextVertices(i)) {
            arcs.push_back({i, to});
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    arcs.push_back({from, to});
}

int ArcGraph::VerticesCount() const {
    return verticesCount;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> nextVertices;
    for (const auto& arc : arcs) {
        if (arc.first == vertex) {
            nextVertices.push_back(arc.second);
        }
    }
    return nextVertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prevVertices;
    for (const auto& arc : arcs) {
        if (arc.second == vertex) {
            prevVertices.push_back(arc.first);
        }
    }
    return prevVertices;
}
