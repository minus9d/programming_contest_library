// 最小全域木(Minimum Spanning Tree)をクラスカル法で作成
// 参考：プログラミングコンテストチャレンジブック 第一版 p101
// verify: SRM788 Div1 Easy

#pragma once
#include "common.h"
#include "data_structure/union_find.h"

// クラスカル法で最小全域木を求める
class Kruskal {

public:

struct edge { ll u, v, cost; };

// ret: 最小全域木のコスト, 最小全域木の構築に使ったエッジ (1: 使用, 0: 不使用)
static tuple<ll, vector<int>> kruskal(vector<edge>& edges, int V)
{ 
    auto E = SIZE(edges);
    using intedge = pair<int, edge>;
    vector<intedge> idx_edges;
    REP(i, E) {
        idx_edges.pb(mp(i, edges[i]));
    }
    sort(ALL(idx_edges), [](const intedge& a, const intedge& b) {
                             return a.second.cost < b.second.cost;
                         });
    UnionFind uf(V);
    ll res = 0;
    vector<int> used_edge_indexes(E);
    REP(i, E) {
        auto index = idx_edges[i].first;
        auto& e = idx_edges[i].second;
        if (!uf.same(e.u, e.v)) {
            uf.unite(e.u, e.v);
            res += e.cost;
            used_edge_indexes[index] = 1;
        }
    }
    return mt(res, used_edge_indexes);
}

};
