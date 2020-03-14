#include "catch.hpp"
#include "graph/lca.h"

TEST_CASE("lca", "[graph]") {
    // 木構造を定義
    int N = 7;  // ノード数
    Graph g(N);
    // 木を構成する辺 (N - 1個)
    vector<pair<int, int>> edges{{0, 1}, {1, 2}, {1, 3}, {2, 4}, {2, 5}, {0, 6}};
    for (auto edge : edges) {
        auto u = edge.first;
        auto v = edge.second;
        g[u].pb(v);
        g[v].pb(u);
    }

    // 0番目のnodeをrootとして、共通祖先のクエリに答える
    LCA lca0(g, 0);
    REQUIRE(2 == lca0.get(4, 5));
    REQUIRE(2 == lca0.get(2, 5));
    REQUIRE(1 == lca0.get(1, 5));
    REQUIRE(1 == lca0.get(3, 5));
    REQUIRE(0 == lca0.get(6, 5));

    // 1番目のnodeをrootとして、共通祖先のクエリに答える
    LCA lca1(g, 1);
    REQUIRE(2 == lca1.get(4, 5));
    REQUIRE(1 == lca1.get(3, 5));
    REQUIRE(0 == lca1.get(0, 6));
    REQUIRE(1 == lca1.get(6, 5));
}
