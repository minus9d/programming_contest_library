// verify: aoj grl_1_b
//         http://abc061.contest.atcoder.jp/tasks/abc061_d


#pragma once
#include "common.h"

// 頂点は0-originとする
template <typename T>
class BellmanFord {
    struct edge {
        int from;
        int to;
        T cost;
    };

public:
    T INF;
    T NINF;

    BellmanFord(int V)
        : INF(std::numeric_limits<T>::max())
        , NINF(std::numeric_limits<T>::min())
        , m_V(V) {
        m_es.clear();
    }

    void add_dir_edge(int from, int to, T cost) {
        m_es.push_back( edge{from, to, cost} );
    }

    void add_undir_twoways(int v1, int v2, T cost) {
        add_dir_edge(v1, v2, cost);
        add_dir_edge(v2, v1, cost);
    }

    // 頂点sから各頂点までの距離を計算してdに格納 負の閉路も検出する
    vector<T> shortest_path(int s)
    {
        // INF: その頂点には到達できない
        // NINF: 負の経路があり、sからの最短距離は-∞
        // INF以外: sからの最短距離
        vector<T> d(m_V, INF);
        vector<char> has_negative_loop(m_V);
        d[s] = 0;
        REP(try_num, m_V) {
            bool update = false;
            REP(i, SIZE(m_es)) {
                edge e = m_es[i];
                if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
                    d[e.to] = d[e.from] + e.cost;
                    update = true;

                    // 無限ループ発見
                    if (try_num == m_V - 1) {
                        has_negative_loop[e.to] = 1;
                    }
                }
            }
            if (!update) break;
        }

        // cout << "dists:" << endl;
        // for (auto e: d) cout << e << " ";
        // cout << endl;
        // cout << "negative loop:" << endl;
        // for (auto e: has_negative_loop) cout << int(e) << " ";
        // cout << endl;

        // sからたどり着くまでにnegative loopが存在するような頂点に関して、
        // その最短路をNINFに書き換える
        REP(i, m_V) {
            if (has_negative_loop[i]) d[i] = NINF;
        }

        return move(d);
    }

    // sから各頂点までの最短路に閉路があるかを返す
    bool find_negative_loop_from_v(int s) {
        vector<T> d(m_V, INF);
        
        d[s] = 0;
        // ループの実行は高々|V|-1回のはず
        // ループの実行回数が|V|よりも大きければ閉路があったとみなす
        int count = 0;
        while (true) {
            bool update = false;
            REP(i, SIZE(m_es)) {
                edge e = m_es[i];
                if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
                    d[e.to] = d[e.from] + e.cost;
                    update = true;
                }
            }
            if (!update) break;

            ++count;
            if (count > m_V) return true;
        }

        return false;
    }

    // グラフ全体のどこかに負の経路があることを検出
    bool find_negative_loop_somewhere(void) {
        vector<T> d(m_V);

        REP(i, SIZE(d)) {
            REP(j, SIZE(m_es)) {
                edge e = m_es[j];
                if (d[e.to] > d[e.from] + e.cost){
                    d[e.to] = d[e.from] + e.cost;
                    // n回目にも更新があるなら負の経路が存在する
                    if (i == SIZE(d) - 1) {
                        return true;
                    }
                }
            }

            // for(int i = 0; i < SIZE(d); ++i) {
            //     cout << d[i] << ", ";
            // }
            // cout << endl;
        }
        return false;
    }

private:
    int m_V;                   
    vector<edge> m_es;
};
