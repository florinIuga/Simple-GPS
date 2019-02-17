// Copyright 2018 Iuga Florin

#ifndef LISTGRAPH_H_
#define LISTGRAPH_H_
#include <algorithm>
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <iostream>
template <typename T>
struct Node {
    std::vector<int> neighbors;
    T value;
};
template <typename T>
class ListGraph {
 private:
    std::vector<Node<T> > nodes;
    int N;

 public:
    explicit ListGraph(int N) {
        this->N = N;
        nodes.resize(N);
    }
    ~ListGraph() {}
    // adauga o muchie intre src si dst
    void addEdge(int src, int dst) {
     for (unsigned int i = 0; i < nodes[src].neighbors.size(); i++) {
        if (nodes[src].neighbors[i] == dst) {
            return;
        }
     }
      nodes[src].neighbors.push_back(dst);
    }
    // intoarce graful transpus
    ListGraph<T> getReverseGraph() {
        ListGraph<T> gr(N);
        for (int i = 0; i < N; ++i)
        {
          std::vector<int> n = getNeighbors(i);
           for (int j = 0; j < n.size(); j++) {
              gr.nodes[n[j]].neighbors.push_back(i);
           }
        }
        return gr;
    }
    std::vector<int> getNeighbors(int node) {
        return nodes[node].neighbors;
    }
};
#endif  // LISTGRAPH_H_
