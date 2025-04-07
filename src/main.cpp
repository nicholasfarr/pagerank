#include <iostream>
#include "AdjacencyList.h"

int main() {
    AdjacencyList graph;
    int edges = 0, iterations = 0;


    std::cin >> edges >> iterations;

    for (int i = 0; i < edges; ++i) {
        std::string from, to;
        std::cin >> from >> to;
        graph.insertEdge(from, to);
    }


    graph.PageRank(iterations);
    return 0;
}