// 二部マッチングを2種類の方法で解く
// 参考：プログラミングコンテストチャレンジブック 第一版 p196, p197

#pragma once
#include "common.h"
#include "max-flow-ford-fulkerson.h"

class BipartiteMatching {
public:
    // V1, V2: 左側・右側それぞれの頂点数
    BipartiteMatching(int V1, int V2) : m_V1(V1), m_V2(V2) {
        m_G.resize(m_V1 + m_V2);
    }
    // 左側の頂点と右側の頂点の間に辺を張る
    void add_edge(int v1, int v2) {
        v2 += m_V1;
        m_G[v1].push_back(v2);
        m_G[v2].push_back(v1);
    }
    // 二部グラフの最大マッチングを求める
    int bipartite_matching() {
        int res = 0;
        m_match.resize(m_V1 + m_V2, -1);
        REP(v, m_V1 + m_V2) {
            if (m_match[v] < 0) {
                m_used.resize(m_V1 + m_V2, 0);
                if (dfs(v)) ++res;
            }
        }
        return res;
    }
    void debug_print() {
        REP(i, SIZE(m_match)) {
            cout << "v" << i << " ";
            auto m = m_match[i];
            if (m == -1) cout << "has no pair" << endl;
            else cout << "is matched with " << m << endl;
        }
    }
    bool has_matching(int u, int v) { return m_match[u] == v; }
private:
    bool dfs(int v) {
        m_used[v] = true;
        for(auto u: m_G[v]) {
            int w = m_match[u];
            if (w < 0 || !m_used[w] && dfs(w)) {
                m_match[v] = u;
                m_match[u] = v;
                return true;
            }
        }
        return false;
    }
    int m_V1;
    int m_V2;
    vector<vector<int>> m_G; // グラフの隣接リスト表現
    vector<int> m_match; // マッチングのペア
    vector<char> m_used; // DFSですでに調べたかのフラグ
};


// 通常使う必要なし
class BipartiteMatchingFF {
public:
    // それぞれの部の頂点の数を指定
    BipartiteMatchingFF(int in_V1, int in_V2)
        : m_V1(in_V1), m_V2(in_V2) {
        // 始点、終点を加えるので+2
        m_ff = new FordFulkerson<int>(m_V1 + m_V2 + 2);
        s = m_V1 + m_V2;
        t = s + 1;
        // 始点から辺を張る
        REP(i, m_V1) m_ff->add_uni_edge(s, i, 1);
        // 終点へ辺を張る
        REP(i, m_V2) m_ff->add_uni_edge(m_V1 + i, t, 1);
    }
    ~BipartiteMatchingFF(void) { delete m_ff; }
    // V1の頂点とV2の頂点の間に辺を張る
    void add_edge(int v1, int v2) { m_ff->add_uni_edge(v1, m_V1 + v2, 1); }
    // 二部グラフの最大マッチングを求める
    int bipartite_matching() { return m_ff->max_flow(s, t); }
private:
    int m_V1; // 始点側の部の要素数
    int m_V2; // 終点側の部の要素数
    int s; // 始点
    int t; // 終点
    FordFulkerson<int>* m_ff;
};
