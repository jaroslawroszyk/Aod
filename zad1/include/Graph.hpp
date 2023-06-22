#pragma once
#include <vector>
#include <queue>
#include "Edge.hpp"
#include <limits>

constexpr int INF = std::numeric_limits<int>::max();

class Graph
{

public:
    Graph(int V);

    void addEdge(int, int, int);

    bool BFS(std::vector<int>&, std::vector<int>&);

    int edmondsKarp(bool);
    int edmondsKarp(int source, int target);
    void printMatching();

private:
    int V;
    std::vector<std::vector<Edge>> adj;
};
