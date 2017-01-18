#include "catch.hpp"
#include "graph/dijkstra.h"

TEST_CASE("dijkstra", "[graph]") {
    Dijkstra<int> dij(5);

    dij.add_dir_edge(0, 1, 1);
    dij.add_dir_edge(1, 2, 2);
    dij.add_dir_edge(2, 3, 3);
    dij.add_dir_edge(0, 3, 10);
    
    auto distances0 = dij.shortest_path(0);
    REQUIRE(distances0[0] == 0);
    REQUIRE(distances0[1] == 1);
    REQUIRE(distances0[2] == 3);
    REQUIRE(distances0[3] == 6);
    auto distances1 = dij.shortest_path(1);
    REQUIRE(distances1[0] == dij.INF);
    REQUIRE(distances1[1] == 0);
    REQUIRE(distances1[2] == 2);
    REQUIRE(distances1[3] == 5);
}
