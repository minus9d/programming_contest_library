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
