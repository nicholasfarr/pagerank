#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
// Created by Nicholas Farr
// Header file for AdjacencyList

class AdjacencyList {
private:
    std::map<std::string, float> pageRank;
    std::unordered_map<std::string, unsigned int> outDegreeGraph;
    std::unordered_map<std::string, std::vector<std::string>> inDegreeGraph;


    void printPageRanks();
    int getNumberOfVertices();
    void initializePageRank();


public:

    AdjacencyList() = default;

    void PageRank(int power_iterations);
    void insertEdge(std::string &from, std::string &to);



};

#endif // ADJACENCYLIST_H