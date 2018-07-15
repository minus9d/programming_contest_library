#include "catch.hpp"
#include "graph/bellman-ford.h"

// TODO: check
TEST_CASE("bellman-ford", "[graph]") {
    BellmanFord<ll> bf(5);

    bf.add_dir_edge(0, 1, 1);
    bf.add_dir_edge(1, 2, 2);
    bf.add_dir_edge(2, 3, 3);
    bf.add_dir_edge(0, 3, 10);
    
    auto distances0 = bf.shortest_path(0);
    REQUIRE(distances0[0] == 0);
    REQUIRE(distances0[1] == 1);
    REQUIRE(distances0[2] == 3);
    REQUIRE(distances0[3] == 6);
    auto distances1 = bf.shortest_path(1);
    REQUIRE(distances1[0] == bf.INF);
    REQUIRE(distances1[1] == 0);
    REQUIRE(distances1[2] == 2);
    REQUIRE(distances1[3] == 5);
}

// 負の閉路がある場合
TEST_CASE("bellman-ford-negative-loop", "[graph]") {
    BellmanFord<ll> bf(5);

    bf.add_dir_edge(0, 1, 1);
    bf.add_dir_edge(1, 2, -1);
    bf.add_dir_edge(2, 1, -1);
    bf.add_dir_edge(2, 3, 3);

    auto distances0 = bf.shortest_path(0);
    REQUIRE(distances0[0] == 0);
    REQUIRE(distances0[1] == bf.NINF);
    REQUIRE(distances0[2] == bf.NINF);
    REQUIRE(distances0[3] == bf.NINF);
    REQUIRE(distances0[4] == bf.INF);
}
