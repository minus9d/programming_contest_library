// 参考：プログラミングコンテストチャレンジブック 第一版 p200, p203

#pragma once
#include "common.h"

class MinCostFlowPotential {

private:
    struct edge { int to, cap, cost, rev; }; // 行き先、容量、コスト、逆辺
    typedef pair<int, int> P;    // <最短距離, 頂点の番号>
    int V;
    vector<vector<edge> > G;
    vector<int> h; // ポテンシャル
    vector<int> dist;
    vector<int> prevv; // 直前の頂点
    vector<int> preve; // 直前の辺
public:
    const int INF = 1e8;
    void init(int v) {
        V = v;
        G.resize(V);
        h.resize(V);
        dist.resize(V);
        prevv.resize(V); // 直前の頂点
        preve.resize(V); // 直前の辺
    }
    void add_edge(int from, int to, int cap, int cost) {
        G[from].push_back( (edge){ to, cap, cost, SIZE(G[to]) } );
        G[to].push_back( (edge){from, 0, -cost, SIZE(G[from]) - 1});
    }
    // sからtまでf流したときの最小コストを求める 流せない時は-1を返す
    int min_cost_flow(int s, int t, int f) {
        int res = 0;
        fill(ALL(h), 0);
        while (f > 0) {
            // dijkstra
            priority_queue<P, vector<P>, greater<P> > que;
            fill(ALL(dist), INF);
            dist[s] = 0;
            que.push(P(0, s));
            while (!que.empty()) {
                P p = que.top();
                que.pop();
                int v = p.second;
                if (dist[v] < p.first) continue;
                REP(i, SIZE(G[v])) {
                    edge &e = G[v][i];
                    if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                        dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        que.push(P(dist[e.to], e.to));
                    }
                }
            }
            if (dist[t] == INF) {
                return -1;
            }
            REP(v, V) h[v] += dist[v];

            int d = f;
            for (int v = t; v != s; v = prevv[v]) {
                d = min(d, G[prevv[v]][preve[v]].cap);
            }
            f -= d;
            res += d * h[t];
            for (int v = t; v != s; v = prevv[v]) {
                edge &e = G[prevv[v]][preve[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return res;
    }
};

// 上記の方法より遅い？　要検証
class MinCostFlowBellmanFord {

// 行き先、容量、コスト、逆辺
struct edge { int to, cap, cost, rev; };
const int INF = 1e8;

private:
    int V;
    vector<vector<edge> > G;
    vector<int> dist;
    vector<int> prevv; // 直前の頂点
    vector<int> preve; // 直前の辺
    
public:
    void init(int v) {
        V = v;
        G.resize(V);
        dist.resize(V);
        prevv.resize(V); // 直前の頂点
        preve.resize(V); // 直前の辺
    }
    void add_edge(int from, int to, int cap, int cost) {
        G[from].push_back( (edge){ to, cap, cost, SIZE(G[to]) } );
        G[to].push_back( (edge){from, 0, -cost, SIZE(G[from]) - 1});
    }
    int min_cost_flow(int s, int t, int f) {
        int res = 0;
        while (f > 0) {
            // bellman-ford
            fill(ALL(dist), INF);
            dist[s] = 0;
            bool update = true;
            while (update) {
                update = false;
                REP(v, V) {
                    if (dist[v] == INF) continue;
                    REP(i, SIZE(G[v])) {
                        edge &e = G[v][i];
                        if (e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
                            dist[e.to] = dist[v] + e.cost;
                            prevv[e.to] = v;
                            preve[e.to] = i;
                            update = true;
                        }
                    }
                }
            }
            if (dist[t] == INF) {
                return -1;
            }
            int d = f;
            for (int v = t; v != s; v = prevv[v]) {
                d = min(d, G[prevv[v]][preve[v]].cap);
            }
            f -= d;
            res += d * dist[t];
            for (int v = t; v != s; v = prevv[v]) {
                edge &e = G[prevv[v]][preve[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return res;
    }
};
