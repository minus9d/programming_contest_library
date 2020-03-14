#pragma once
#include "common.h"

// https://github.com/drken1215/algorithm/blob/master/DataStructureOnTree/LCA_doubling.cpp からコピーして作成
// 共通最小祖先(LCA)を求める  ダブリングによる実装

// 木を表すデータ構造  e.g. g[s] = {t, u}のとき、sはt, uと辺で繋がっていることを意味する
using Graph = vector<vector<int> >;
struct LCA {
    // G: tree  r: rootとなるnode
    LCA(const Graph &G, int root) { init(G, root); }
    // uとvの共通最小祖先を求める
    int get(int u, int v) {
        // uのほうが浅いとする
        if (depth[u] > depth[v]) swap(u, v);
        // uと同じ深さになるまでvのparentを辿る
        REP(i, SIZE(parent))
            if ( (depth[v] - depth[u]) & (1<<i) )
                v = parent[i][v];
        // ちょうどuとvが同じ、すなわち共通最小祖先はu (= v)
        if (u == v) return u;

        // u, pそれぞれの1個上のparentが共通最小祖先になるまで、uとvのparentを辿る
        // uとvの共通祖先を、2^n, 2-(n-1), ..., 4, 2, 1個上から順に見ていく
        // 例えばuの16個上のparentと, vの16個上のparentの一致をチェックして
        // 一致する場合:
        //   共通祖先は1~16個上のどこか
        // 一致しない場合:
        //   共通祖先は17~個上のどこか
        for (int i = (int)parent.size()-1; i >= 0; --i) {
            if (parent[i][u] != parent[i][v]) {
                u = parent[i][u];
                v = parent[i][v];
            }
        }
        // uのparent == vのparent == 共通最小祖先
        return parent[0][u];
    }
private:
    void init(const Graph &G, int root) {
        int V = (int)G.size();
        int h = 1;
        while ((1<<h) < V) ++h;
        parent.assign(h, vector<int>(V, -1));
        depth.assign(V, -1);
        dfs(G, root, -1, 0);
        // 2, 4, 8, 16, ...個上のparentを順に決めていく
        // 例えば8個上のparentは、4個上のparentの、さらに4個上のparentを見れば分かる
        for (int i = 0; i + 1 < (int)parent.size(); ++i)
            for (int v = 0; v < V; ++v)
                if (parent[i][v] != -1)
                    parent[i+1][v] = parent[i][parent[i][v]];
    }
    // すべての頂点vについて、rootからのdepthと、1個上のparentを求める
    void dfs(const Graph &G, int v, int p, int d) {
        parent[0][v] = p;
        depth[v] = d;
        for (auto e : G[v]) if (e != p) dfs(G, e, v, d+1);
    }
    // 各vについて、1, 2, 4, 8, 16, ...個上のparentを記録
    // parent[d][v] := 2^d-th parent of v
    vector<vector<int> > parent;
    // 各vのrootからの深さ
    vector<int> depth;
};


