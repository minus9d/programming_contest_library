// verify: aoj grl_1_c
#pragma once
#include "common.h"

template <typename T>
class WarshallFloyd {
private:
    int m_V;                   
    vector<vector<T>> m_d;
    
public:
    T INF;
    
    WarshallFloyd(int V)
        : INF(std::numeric_limits<T>::max()/2)
        , m_V(V) {

        // 辺のコストを初期化
        // 辺が存在しないときはINFとする
        m_d.resize(m_V, vector<T>(m_V, INF));
        REP(i,V) m_d[i][i] = 0;
    }

    void add_dir_edge(int from, int to, int cost) {
        m_d[from][to] = cost;
    }

    void add_undir_twoways(int v1, int v2, int cost) {
        add_dir_edge(v1, v2, cost);
        add_dir_edge(v2, v1, cost);
    }

    // 全点間の最短距離を求める
    vector<vector<T>> shortest_path() {
        REP(k, m_V){
            REP(i, m_V){
                REP(j, m_V){
                    // 辺が存在するときのみ短縮できる
                    if(m_d[i][k] != INF && m_d[k][j] != INF)
                        m_d[i][j] = min(m_d[i][j], m_d[i][k] + m_d[k][j]);
                }
            }
        }
        return m_d;
    }

    // shortest_pathを呼んだあとに呼ぶこと
    bool has_negative_loop() {
        REP(i, m_V) {
            if (m_d[i][i] < 0) return true;
        }
        return false;
    }
};


