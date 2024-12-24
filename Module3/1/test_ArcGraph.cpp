#include "ArcGraph.h"
#include <cassert>
#include <iostream>

void TestArcGraph() {
    ArcGraph graph(5);  
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(3, 4);

    assert(graph.VerticesCount() == 5);

    std::vector<int> next = graph.GetNextVertices(0);
    assert((next == std::vector<int>{1, 2}));

    std::vector<int> prev = graph.GetPrevVertices(3);
    assert((prev == std::vector<int>{1}));

    ArcGraph copiedGraph(graph);
    assert(copiedGraph.VerticesCount() == 5);
    std::vector<int> nextCopied = copiedGraph.GetNextVertices(0);
    assert((nextCopied == std::vector<int>{1, 2}));

    std::cout << "ArcGraph test passed!" << std::endl;
}

int main() {
    TestArcGraph();
    return 0;
}
