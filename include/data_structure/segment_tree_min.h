#pragma once
#include "common.h"

template <typename T>
class SegmentTreeMin
{
private:
    T INF;
    int m_n;
    vector<T> m_dat;
public:
    SegmentTreeMin(int n)
        : INF(std::numeric_limits<T>::max()) {
        m_n = 1;
        while  (m_n < n) m_n *= 2;
        m_dat.resize(2 * m_n - 1, INF);
    };
    void update(int k, T val) {
        k += m_n - 1;
        m_dat[k] = val;
        while (k > 0) {
            k = (k - 1) / 2;
            m_dat[k] = min(m_dat[k * 2 + 1], m_dat[k * 2 + 2]);
        }
    }
    // [a, b)の範囲で最小値を返す
    T query(int a, int b) {
        return queryInternal(a, b, 0, 0, m_n);
    }
private:
    T queryInternal(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) return INF;
        if (a <= l && r <= b) return m_dat[k];
        else {
            T vl = queryInternal(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = queryInternal(a, b, k * 2 + 2, (l + r) / 2, r);
            return min(vl, vr);
        }
    }
};

// (最小値, 最小値をとるインデックス)のペアを返す
// 複数の値が同時に最小値を取る場合はどちらのインデックスが返るか保証がないので注意
// 戻る値など要確認！！！
template <typename T>
class SegmentTreeMinWithIndex
{
private:
    T INF;
    int m_n;
    vector<pair<T,int>> m_dat; // (min, idx)のペア
public:
    SegmentTreeMinWithIndex(int n)
        : INF(std::numeric_limits<T>::max()) {
        m_n = 1;
        while  (m_n < n) m_n *= 2;
        m_dat.resize(2 * m_n - 1, mp(INF,-1));
    }
    void update(int k, T val) {
        int orig_k = k;
        k += m_n - 1;
        m_dat[k] = mp(val,orig_k);
        while (k > 0) {
            k = (k - 1) / 2;
            auto v1 = m_dat[k * 2 + 1].first;
            auto v2 = m_dat[k * 2 + 2].first;
            if (v1 < v2) m_dat[k] = mp(v1, m_dat[k * 2 + 1].second);
            else m_dat[k] = mp(v2, m_dat[k * 2 + 2].second);
        }
    }
    // [a, b)の範囲で(min, idx)のペアを返す
    pair<T,int> query(int a, int b) {
        return queryInternal(a, b, 0, 0, m_n);
    }
private:
    pair<T,int> queryInternal(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) return mp(INF,-1);
        if (a <= l && r <= b) return m_dat[k]; // ?
        else {
            auto vl = queryInternal(a, b, k * 2 + 1, l, (l + r) / 2);
            auto vr = queryInternal(a, b, k * 2 + 2, (l + r) / 2, r);
            return (vl.first < vr.first) ? vl : vr;
        }
    }
};
