// 最大流問題を、Ford-Fulkerson法で解く
// 参考：プログラミングコンテストチャレンジブック 第一版 p190
#pragma once
#include "common.h"

template <typename T>
class FordFulkerson {
private:
    struct edge { int to, T cap, T rev; }; // 行き先、容量、逆辺
    とちゅう
    const int INF = 1e9;
    vector<vector<edge>> G;
    vector<char> used;
public:
    FordFulkerson(int V) {
        G.resize(V);
        used.resize(V);
    }
    void add_uni_edge(int from, int to, int cap) {
        // revには、逆辺の容量をすぐに得るためのインデックスを記録
        G[from].push_back( edge{ to, cap, SIZE(G[to])});
        G[to].push_back( edge{from, 0, SIZE(G[from]) - 1});
    }
    // 未テスト
    void add_bi_edge(int v1, int v2, int cap) {
        add_uni_edge(v1, v2, cap);
        add_uni_edge(v2, v1, cap);
    }
    int max_flow(int s, int t) {
        int flow = 0;
        while (true) {
            fill(ALL(used), 0);
            int f = dfs(s, t, INF);
            if (f == 0) return flow;
            flow += f;
        }
    }
    void debug_print() {
        REP(from, SIZE(G)){
            cout << "from " << from << ": " << endl;
            for (auto e : G[from]) {
                printf(" -> %d, capacity(%d), rev(%d)\n", e.to, e.cap, G[e.to][e.rev].cap);
            }
            cout << endl;
        }
    }
private:
    // vからtまでの最大流を返す
    // fは、頂点vの時点でわかっている可能な最大流の大きさ??
    int dfs(int v, int t, int f) {
        if (v == t) return f;
        used[v] = true;
        // v番目の頂点が持つ辺でループ
        REP(i, SIZE(G[v])) {
            edge &e = G[v][i];
            // まだ辺eに余裕がある場合
            if (!used[e.to] && e.cap > 0) {
                int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
};
