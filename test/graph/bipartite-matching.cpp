#include "catch.hpp"
#include "graph/bipartite-matching.h"

TEST_CASE("bipartite-matching", "[graph]") {
    // コンピュータの数
    const int N = 4;
    // 人の数
    const int K = 6;

    BipartiteMatching bm(N + K);

    bm.add_edge(0, 0 + N);
    bm.add_edge(0, 1 + N);
    bm.add_edge(0, 2 + N);
    bm.add_edge(1, 3 + N);
    bm.add_edge(2, 1 + N);
    bm.add_edge(3, 4 + N);

    int max_pair = bm.bipartite_matching();
    REQUIRE(max_pair == 4);
}
