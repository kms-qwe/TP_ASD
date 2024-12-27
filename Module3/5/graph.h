#ifndef GRAPH_H
#define GRAPH_H

#include "point.h"
#include <vector>

struct Edge {
    int to;
    double weight;
    bool operator>( const Edge& other) const { return weight > other.weight; }
};

class Graph {
public:
    Graph(int n, const std::vector<Point>& points);
    std::pair<double, std::vector<int>> findTspPath();    
    const std::vector<std::vector<Edge>>& getAdjList() const;
    double exactTSP(const std::vector<Point>& points); 


private:
    void preorderTraversal(int v, const std::vector<std::vector<int>>& mstAdjList, std::vector<bool>& visited, std::vector<int>& path);

    int n;
    std::vector<std::vector<Edge>> adjList;
};

#endif
