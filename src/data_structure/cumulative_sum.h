#pragma once
#include "common.h"

// 1次元累積和
template <typename T>
class CumSum1D
{
public:
    CumSum1D(){};
    ~CumSum1D(){};
    void init(vector<T>& arr) {
        m_cum = arr;
        m_N = arr.size();
        FOR(i, 1, m_N) m_cum[i] += m_cum[i - 1];
    }
    // get sum of [l, r]. 0-based.
    T getSum(int l, int r) {
        T ret = m_cum[r];
        if (l != 0) ret -= m_cum[l - 1];
        return ret;
    }
private:
    size_t m_N;
    vector<T> m_cum;
};



// 2次元累積和。Integrarl Image(積分画像)ともいう
template <typename T>
class CumSum2D
{
public:
    CumSum2D(){};
    ~CumSum2D(){};
    void init(vector<vector<T>>& arr) {
        m_cum = arr;
        m_H = arr.size();
        m_W = arr[0].size();
        REP(h, m_H) {
            FOR(w, 1, m_W) {
                m_cum[h][w] += m_cum[h][w - 1];
            }
            if (h != 0) {
                REP(w, m_W) m_cum[h][w] += m_cum[h - 1][w];
            }
        }
        REP(h, m_H) {
            REP(w, m_W) {
                 cout << m_cum[h][w] << " ";
            }
            cout << endl;
        }
    }
    // 長方形の中の要素の合計を返す。長方形の左上は[x1, y1], 右下は[x2, y2]。両端を含む
    T getSum(int x1, int y1, int x2, int y2) {
        auto ret = m_cum[y2][x2];
        if (y1 != 0) ret -= m_cum[y1 - 1][x2];
        if (x1 != 0) ret -= m_cum[y2][x1 - 1];
        if (x1 != 0 && y1 != 0) ret += m_cum[y1 - 1][x1 - 1];
        return ret;
    }
private:
    size_t m_H;
    size_t m_W;
    vector<vector<T>> m_cum;
};
