#include "catch.hpp"
#include "graph/bipartite-matching.h"

TEST_CASE("bipartite-matching", "[graph]") {
    // コンピュータの数
    const int N = 4;
    // 人の数
    const int K = 6;

    BipartiteMatching bm(N, K);

    bm.add_edge(0, 0);
    bm.add_edge(0, 1);
    bm.add_edge(0, 2);
    bm.add_edge(1, 3);
    bm.add_edge(2, 1);
    bm.add_edge(3, 4);

    int max_pair = bm.bipartite_matching();
    REQUIRE(max_pair == 4);
}

TEST_CASE("bipartite-matching-ff", "[graph]") {
    const int N = 4;
    const int K = 6;
    BipartiteMatchingFF bm(N, K);

    bm.add_edge(0, 0);
    bm.add_edge(0, 1);
    bm.add_edge(0, 2);
    bm.add_edge(1, 3);
    bm.add_edge(2, 1);
    bm.add_edge(3, 4);

    int max_pair = bm.bipartite_matching();
    REQUIRE(max_pair == 4);
}
