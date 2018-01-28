#pragma once
#include "common.h"

class BipartiteMatching {
public:
    // V: 両側の頂点数の和
    BipartiteMatching(int V) : m_V(V) {
        m_G.resize(m_V);
    }
    // Uの頂点とVの頂点の間に辺を張る (u: 左側  v: 右側)
    void add_edge(int u, int v) {
        m_G[u].push_back(v);
        m_G[v].push_back(u);
    }
    // 二部グラフの最大マッチングを求める
    int bipartite_matching() {
        int res = 0;
        m_match.resize(m_V, -1);
        REP(v, m_V) {
            if (m_match[v] < 0) {
                m_used.resize(m_V, 0);
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
    int m_V; // 両側の頂点数の合計
    vector<vector<int>> m_G; // グラフの隣接リスト表現
    vector<int> m_match; // マッチングのペア
    vector<char> m_used; // DFSですでに調べたかのフラグ
};
