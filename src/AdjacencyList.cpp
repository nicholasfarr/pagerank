#include "AdjacencyList.h"
#include <iostream>
#include <iomanip>
// Created by Nicholas Farr - Pagerank Algorithm for Data Structures and Algorithms UF COP3530



void AdjacencyList::printPageRanks() {
    for (auto &pageRankEntry : pageRank) {
        std::cout << std::fixed << std::setprecision(2)
                  << pageRankEntry.first << " " << pageRankEntry.second << "\n";
    }
}

void AdjacencyList::initializePageRank() {
    int totalVertexCount = getNumberOfVertices();
    for (auto &vertexPair : inDegreeGraph) {
        pageRank[vertexPair.first] = 1.0f / static_cast<float>(totalVertexCount);
    }
}



void AdjacencyList::insertEdge(std::string &from, std::string &to) {
    // Increase out-degree
    outDegreeGraph[from] += 1;
    inDegreeGraph[to].push_back(from);

    if (outDegreeGraph.find(to) == outDegreeGraph.end()) {
        outDegreeGraph[to] = 0;
    }
    if (inDegreeGraph.find(from) == inDegreeGraph.end()) {
        inDegreeGraph[from] = {};
    }
}



int AdjacencyList::getNumberOfVertices() {
    return static_cast<int>(inDegreeGraph.size());
}


// The holy grail algorithm
void AdjacencyList::PageRank(int powerIterations) {

    // initialize page rank
    initializePageRank();

    // Updated ranks
    std::map<std::string, float> updatedPageRank;

    //  iterative updates
    for (int iteration = 1; iteration < powerIterations; iteration++) {
        updatedPageRank = pageRank;

        // calculate contributions from inbound links
        for (auto &nodeEntry : inDegreeGraph) {
            float sumContributions = 0.0f;
            for (auto &srcNode : nodeEntry.second) {
                sumContributions += pageRank[srcNode] / static_cast<float>(outDegreeGraph[srcNode]);
            }
            updatedPageRank[nodeEntry.first] = sumContributions;
        }

        // Update the official PageRank values
        pageRank = updatedPageRank;
    }
    // Print final results
    printPageRanks();
}
