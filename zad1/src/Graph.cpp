#include "Graph.hpp"
#include "Edge.hpp"
#include <vector>
#include <queue>
#include <iostream>

Graph::Graph(int V) : V(V)
{
    adj.resize(V);
}

void Graph::addEdge(int u, int v, int capacity)
{
    Edge uv{ v, capacity, 0, capacity };
    Edge vu{ u, 0, 0, 0 };
    adj[u].push_back(uv);
    adj[v].push_back(vu);
}

bool Graph::BFS(std::vector<int>& parent, std::vector<int>& minCapacity)
{
    std::vector<bool> visited(V, false);
    std::queue<int> q;

    visited[0] = true;
    minCapacity[0] = INF;
    q.push(0);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (const auto& edge : adj[u])
        {
            int v = edge.v;
            int residual = edge.residual;

            if (not visited[v] && residual > 0)
            {
                visited[v] = true;
                parent[v] = u;
                minCapacity[v] = std::min(minCapacity[u], residual);
                q.push(v);

                if (v == V - 1)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

int Graph::edmondsKarp(bool printFlow)
{
    std::vector<int> parent(V, -1);
    std::vector<int> minCapacity(V, 0);
    int maxFlow = 0;

    while (BFS(parent, minCapacity))
    {
        int pathCapacity = minCapacity[V - 1];
        maxFlow += pathCapacity;

        int v = V - 1;
        while (v != 0)
        {
            int u = parent[v];

            for (auto& edge : adj[u])
            {
                if (edge.v == v)
                {
                    edge.flow += pathCapacity;
                    edge.residual -= pathCapacity;
                    break;
                }
            }

            for (auto& edge : adj[v])
            {
                if (edge.v == u)
                {
                    edge.flow -= pathCapacity;
                    edge.residual += pathCapacity;
                    break;
                }
            }

            v = u;
        }
    }

    if (printFlow)
    {
        printMatching();
    }

    return maxFlow;
}

void Graph::printMatching()
{
    for (int u = 0; u < V; ++u)
    {
        for (const Edge& edge : adj[u])
        {
            if (edge.flow > 0)
            {
                std::cout << u << " -> " << edge.v << " : " << edge.flow << std::endl;
            }
        }
    }
}