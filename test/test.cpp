#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "AdjacencyList.h"

using namespace std;

TEST_CASE("Handles graph with single node", "[single_node]") {
    string input = R"(1 0
a.com b.com
)";
    string expectedOutput = R"(a.com 1.00
)";

    string actualOutput;

    // AdjacencyList g;
    // g.parseInput(input);
    // actualOutput = g.getStringRepresentation();

    REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("Handles graph with dead end node", "[dead_end]") {
    string input = R"(2 1
a.com b.com
)";
    string expectedOutput = R"(a.com 0.50
b.com 0.50
)";

    string actualOutput;

    // AdjacencyList g;
    // g.parseInput(input);
    // actualOutput = g.getStringRepresentation();

    REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("PageRank redistributes properly after iterations", "[iterations]") {
    string input = R"(3 3
a.com b.com
b.com c.com
c.com a.com
)";
    string expectedOutput = R"(a.com 0.33
b.com 0.33
c.com 0.33
)";

    string actualOutput;

    // AdjacencyList g;
    // g.parseInput(input);
    // g.runIterations(100);
    // actualOutput = g.getStringRepresentation();

    REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("Graph with multiple outgoing edges", "[multi_outgoing]") {
    string input = R"(3 2
a.com b.com
a.com c.com
)";
    string expectedOutput = R"(a.com 0.15
b.com 0.425
c.com 0.425
)";

    string actualOutput;

    // AdjacencyList g;
    // g.parseInput(input);
    // actualOutput = g.getStringRepresentation();

    REQUIRE(actualOutput == expectedOutput);
}

// Nicholas Farr: UFID 17993779
TEST_CASE("Handles disconnected graph", "[disconnected]") {
    string input = R"(4 2
a.com b.com
c.com d.com
)";
    string expectedOutput = R"(a.com 0.25
b.com 0.25
c.com 0.25
d.com 0.25
)";

    string actualOutput;

    // AdjacencyList g;
    // g.parseInput(input);
    // actualOutput = g.getStringRepresentation();

    REQUIRE(actualOutput == expectedOutput);
}
