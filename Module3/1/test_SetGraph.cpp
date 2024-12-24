#include "SetGraph.h"
#include <cassert>
#include <iostream>
#include <algorithm> 

void TestSetGraph() {
    SetGraph graph(5);  
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(3, 4);

    assert(graph.VerticesCount() == 5);

    std::vector<int> next = graph.GetNextVertices(0);
    std::sort(next.begin(), next.end());  
    assert((next == std::vector<int>{1, 2}));

    std::vector<int> prev = graph.GetPrevVertices(3);
    std::sort(prev.begin(), prev.end());  
    assert((prev == std::vector<int>{1}));

    SetGraph copiedGraph(graph);
    assert(copiedGraph.VerticesCount() == 5);
    std::vector<int> nextCopied = copiedGraph.GetNextVertices(0);
    std::sort(nextCopied.begin(), nextCopied.end()); 
    assert((nextCopied == std::vector<int>{1, 2}));

    std::cout << "SetGraph test passed!" << std::endl;
}

int main() {
    TestSetGraph();
    return 0;
}
