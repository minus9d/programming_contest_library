#include "catch.hpp"
#include "graph/kruskal.h"

TEST_CASE("kruskal", "[graph]") {
    int V = 7;

    // (頂点0から頂点2までのコストは1), ...
    // p99の絵に従う
    vector<Kruskal::edge> edges = { {0, 2, 1}, {1, 2, 2}, {1, 4, 10},
                           {2, 3, 3}, {2, 5, 7},
                           {3, 5, 1}, {3, 6, 5},
                           {4, 5, 5}, {5, 6, 8} };
  
  // 頂点0から、他の頂点までのコストを計算
    auto ret = Kruskal::kruskal(edges, V);
    auto mincost = get<0>(ret);
    auto used_edge_indexes = get<1>(ret);

    // 結果を表示
    REQUIRE(mincost == 17);
}
