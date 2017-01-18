#include "catch.hpp"
#include "graph/warshall-floyd.h"

TEST_CASE("warshall-floyd", "[graph]") {
    WarshallFloyd<ll> wf(5);

    wf.add_dir_edge(0, 1, 1);
    wf.add_dir_edge(1, 2, 2);
    wf.add_dir_edge(2, 3, 3);
    wf.add_dir_edge(0, 3, 10);
 
    auto distance_matrix = wf.shortest_path();
    REQUIRE(distance_matrix[0][0] == 0);
    REQUIRE(distance_matrix[0][1] == 1);
    REQUIRE(distance_matrix[0][2] == 3);
    REQUIRE(distance_matrix[0][3] == 6);
    REQUIRE(distance_matrix[1][0] == wf.INF);
    REQUIRE(distance_matrix[1][1] == 0);
    REQUIRE(distance_matrix[1][2] == 2);
    REQUIRE(distance_matrix[1][3] == 5);
}
