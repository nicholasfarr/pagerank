// test.cpp

#include <catch2/catch_all.hpp>   // Includes all Catch2 headers, including Approx
#define CATCH_CONFIG_MAIN
#include "catch.hpp"      // Make sure this points to your Catch2 header
#include "pagerank.h"     // Adjust this include to your PageRank implementation header
#include <vector>
#include <cmath>

// Tolerance for floating-point comparisons
const double TOL = 1e-4;

// Helper function to compute the sum of vector entries.
double sumVector(const std::vector<double>& vec) {
    double sum = 0.0;
    for (double v : vec)
        sum += v;
    return sum;
}

//
// Test Case 1: Single Node Graph
//
TEST_CASE("Single Node", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {} };
    auto pr = computePageRank(graph);
    REQUIRE(pr.size() == 1);
    REQUIRE(pr[0] == Approx(1.0).epsilon(TOL));
}

//
// Test Case 2: Two Nodes, One Directional Edge (0 -> 1)
//
TEST_CASE("Two Nodes, One directional edge", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {1}, {} };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
    // Expect node 1 to receive more PageRank because it is linked from node 0.
    REQUIRE(pr[1] > pr[0]);
}

//
// Test Case 3: Two Nodes, Bidirectional Edges (0 <-> 1)
//
TEST_CASE("Two Nodes, Bidirectional edges", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {1}, {0} };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
    // Both nodes should have equal rank.
    REQUIRE(pr[0] == Approx(pr[1]).epsilon(TOL));
}

//
// Test Case 4: Self-Loop (Single Node with a loop)
//
TEST_CASE("Self Loop", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {0} };
    auto pr = computePageRank(graph);
    REQUIRE(pr.size() == 1);
    REQUIRE(pr[0] == Approx(1.0).epsilon(TOL));
}

//
// Test Case 5: Isolated Node with an Incoming Edge (Graph: [ {}, {0} ])
//
TEST_CASE("Isolated Node with Incoming Edge", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {}, {0} };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
    // Node 0 should receive more PageRank via the incoming link.
    REQUIRE(pr[0] > pr[1]);
}

//
// Test Case 6: Graph with a Dangling Node (Graph: [ {1}, {2}, {} ])
//
TEST_CASE("Dangling Node", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {1}, {2}, {} };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
    // Expect the dangling node (node 2) to gain extra rank through distribution.
    REQUIRE(pr[2] > pr[0]);
    REQUIRE(pr[2] > pr[1]);
}

//
// Test Case 7: Simple 3-Node Cycle (0->1, 1->2, 2->0)
//
TEST_CASE("3-Node Cycle", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {1}, {2}, {0} };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
    // In a perfect cycle, expect a uniform distribution.
    for (double v : pr) {
        REQUIRE(v == Approx(1.0/3).epsilon(TOL));
    }
}

//
// Test Case 8: Disconnected Graph (Two nodes cycle and one isolated)
// Graph: Component 1: 0<->1 ; Component 2: node 2 isolated
//
TEST_CASE("Disconnected Graph", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {1}, {0}, {} };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
    // Nodes 0 and 1 are mutually linked.
    REQUIRE(pr[0] == Approx(pr[1]).epsilon(TOL));
}

//
// Test Case 9: Complete Graph of 3 Nodes (each node links to every other node)
//
TEST_CASE("Complete Graph", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {1,2}, {0,2}, {0,1} };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
    for (double v : pr) {
        REQUIRE(v == Approx(1.0/3).epsilon(TOL));
    }
}

//
// Test Case 10: Star Graph (Central node pointing to 3 dangling nodes)
// Graph: 0 -> {1,2,3}; nodes 1,2,3 are dangling.
//
TEST_CASE("Star Graph", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {1,2,3}, {}, {}, {} };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
    // Expect the center node (node 0) to have a higher rank.
    REQUIRE(pr[0] > pr[1]);
    REQUIRE(pr[0] > pr[2]);
    REQUIRE(pr[0] > pr[3]);
}

//
// Test Case 11: Graph with Multiple Edges
// Graph: 0 -> {1,2,3,4}; 1 -> {3}; 2 -> {3}; 3 -> {0}; 4 -> {0}
//
TEST_CASE("Graph with Multiple Edges", "[pagerank]") {
    std::vector<std::vector<int>> graph = {
        {1,2,3,4},
        {3},
        {3},
        {0},
        {0}
    };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
    // Expect node 0 to accumulate more rank from incoming links.
    REQUIRE(pr[0] > pr[1]);
    REQUIRE(pr[0] > pr[2]);
}

//
// Test Case 12: Larger Cycle (5-Node Cycle)
// Graph: 0->1, 1->2, 2->3, 3->4, 4->0
//
TEST_CASE("5-Node Cycle", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {1}, {2}, {3}, {4}, {0} };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
    for (double v : pr) {
        REQUIRE(v == Approx(1.0/5).epsilon(TOL));
    }
}

//
// Test Case 13: Graph with Branching Structure
// Graph: 0 -> {1,2}; 1 -> {3}; 2 -> {3}; 3 -> {0}
//
TEST_CASE("Branching Graph", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {1,2}, {3}, {3}, {0} };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
    // Nodes 0 and 3, which are in the cycle, are expected to be similar.
    REQUIRE(pr[0] == Approx(pr[3]).epsilon(TOL));
}

//
// Test Case 14: Dead-end and Spider Trap
// Graph: 0 -> {1,2}; 1 -> {2}; 2 -> {1}; 3 isolated
//
TEST_CASE("Dead-end and Spider Trap", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {1,2}, {2}, {1}, {} };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
}

//
// Test Case 15: Chain Graph
// Graph: 0->1, 1->2, 2->3, 3->4, where 4 is dangling.
//
TEST_CASE("Chain Graph", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {1}, {2}, {3}, {4}, {} };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
    // Expect later nodes in the chain to have higher rank.
    REQUIRE(pr[4] > pr[0]);
}

//
// Test Case 16: Reverse Chain Graph
// Graph: 4->3, 3->2, 2->1, 1->0 (node 0 is dangling)
//
TEST_CASE("Reverse Chain Graph", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {}, {0}, {1}, {2}, {3} };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
    // With the chain reversed, expect node 0 to acquire a higher rank.
    REQUIRE(pr[0] > pr[4]);
}

//
// Test Case 17: Two Disjoint Cycles
// Cycle 1: 0->1->2->0; Cycle 2: 3->4->5->3
//
TEST_CASE("Two Disjoint Cycles", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {1}, {2}, {0}, {4}, {5}, {3} };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
    // Within each cycle, the nodes should have similar values.
    REQUIRE(pr[0] == Approx(pr[1]).epsilon(TOL));
    REQUIRE(pr[1] == Approx(pr[2]).epsilon(TOL));
    REQUIRE(pr[3] == Approx(pr[4]).epsilon(TOL));
    REQUIRE(pr[4] == Approx(pr[5]).epsilon(TOL));
}

//
// Test Case 18: Two Cycles Connected by an Edge
// Use the previous cycles then add an extra edge from node 0 to node 3.
//
TEST_CASE("Connected Cycles", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {1,3}, {2}, {0}, {4}, {5}, {3} };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
    // Expect the cycle that receives the extra link (cycle with node 0) to have increased rank compared to the other cycle.
    REQUIRE(pr[0] > pr[3]);
}

//
// Test Case 19: Self-loop with Cross Link
// Graph: 0 -> {0,1}; 1 -> {0,2}; 2 -> {0}
//
TEST_CASE("Self-loop with Cross Link", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {0,1}, {0,2}, {0} };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
    // The self loop on node 0 should help it accumulate rank.
    REQUIRE(pr[0] > pr[1]);
    REQUIRE(pr[0] > pr[2]);
}

//
// Test Case 20: Graph with Multiple Dangling Nodes
// Graph: 0->1; 1->2; 2 is dangling; 3 is dangling; 4->3
//
TEST_CASE("Multiple Dangling Nodes", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {1}, {2}, {}, {}, {3} };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
}

//
// Test Case 21: Symmetric Structure (2x2 Grid)
// Graph: 0 -> {1,2}; 1 -> {0,3}; 2 -> {0,3}; 3 -> {1,2}
//
TEST_CASE("Symmetric 2x2 Grid", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {1,2}, {0,3}, {0,3}, {1,2} };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
    // Due to symmetry, all nodes should have the same PageRank.
    REQUIRE(pr[0] == Approx(pr[1]).epsilon(TOL));
    REQUIRE(pr[1] == Approx(pr[2]).epsilon(TOL));
    REQUIRE(pr[2] == Approx(pr[3]).epsilon(TOL));
}

//
// Test Case 22: Cycle with a Self-loop in the Cycle
// Graph: 0->1; 1->2; 2-> {0,2}
//
TEST_CASE("Cycle with Self-loop", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {1}, {2}, {0,2} };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
    // With the cycle, expect roughly uniform distribution (allow a bit more tolerance).
    for(auto v : pr) {
        REQUIRE(v == Approx(1.0/3).epsilon(0.05));
    }
}

//
// Test Case 23: Complex Graph Structure
// Graph with 6 nodes:
// 0 -> {1,2}
// 1 -> {2,3}
// 2 -> {3,4}
// 3 -> {4,0}
// 4 -> {5}
// 5 -> {0,1}
//
TEST_CASE("Complex Graph Structure", "[pagerank]") {
    std::vector<std::vector<int>> graph = {
        {1,2},
        {2,3},
        {3,4},
        {4,0},
        {5},
        {0,1}
    };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
}

//
// Test Case 24: Isolated Clusters
// Cluster 1 (nodes 0,1,2): fully connected (without self loops)
// Cluster 2 (nodes 3,4): two nodes with mutual link
// Cluster 3 (node 5): isolated
//
TEST_CASE("Isolated Clusters", "[pagerank]") {
    std::vector<std::vector<int>> graph = {
        {1,2},   // Cluster 1
        {0,2},
        {0,1},
        {4},     // Cluster 2
        {3},
        {}       // Isolated node
    };
    auto pr = computePageRank(graph);
    REQUIRE(sumVector(pr) == Approx(1.0).epsilon(TOL));
    // Within cluster 1
    REQUIRE(pr[0] == Approx(pr[1]).epsilon(TOL));
    REQUIRE(pr[1] == Approx(pr[2]).epsilon(TOL));
    // Within cluster 2
    REQUIRE(pr[3] == Approx(pr[4]).epsilon(TOL));
}

//
// Test Case 25: Damping Factor Variation
// Using a 5-node cycle, compute with two different damping factors (0.95 and 0.85)
// and ensure that at least one rank value differs by more than our tolerance.
//
TEST_CASE("Damping Factor Variation", "[pagerank]") {
    std::vector<std::vector<int>> graph = { {1}, {2}, {3}, {4}, {0} };
    auto pr_high = computePageRank(graph, 0.95, 100, TOL);
    auto pr_standard = computePageRank(graph, 0.85, 100, TOL);
    bool differenceFound = false;
    for (size_t i = 0; i < pr_high.size(); i++) {
        if (std::fabs(pr_high[i] - pr_standard[i]) > TOL) {
            differenceFound = true;
            break;
        }
    }
    REQUIRE(differenceFound == true);
}