// 参考：プログラミングコンテストチャレンジブック 第一版 p155
#pragma once
#include "common.h"

template <typename T>
class SegmentTreeMin
{
private:
    int m_n;
    vector<T> m_dat;
public:
    const T INF = std::numeric_limits<T>::max();
    SegmentTreeMin(int n) {
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

// Not verified
template <typename T>
class SegmentTreeMax
{
private:
    SegmentTreeMin<T> m_st;
public:
    SegmentTreeMax(int n) : m_st(n) {};
    void update(int k, T val) {
        m_st.update(k, -val);
    }
    // [a, b)の範囲で最大値を返す
    T query(int a, int b) {
        return -m_st.query(a, b);
    }
};


// <最小値, 最小値をとるインデックス>のペアを返す
// 複数の値が同時に最小値を取る場合はどちらのインデックスが返るか保証がないので注意
// verify: http://agc005.contest.atcoder.jp/tasks/agc005_b
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

// <最大値, 最大値をとるインデックス>のペアを返す
// 複数の値が同時に最大値を取る場合はどちらのインデックスが返るか保証がないので注意
// Not verified
template <typename T>
class SegmentTreeMaxWithIndex
{
private:
    SegmentTreeMinWithIndex<T> m_st;
public:
    SegmentTreeMaxWithIndex(int n) : m_st(n) {}
    void update(int k, T val) {
        m_st.update(k, -val);
    }
    // [a, b)の範囲で(max, idx)のペアを返す
    pair<T,int> query(int a, int b) {
        auto ret = m_st.query(a, b);
        ret.first *= -1;
        return ret;
    }
};
