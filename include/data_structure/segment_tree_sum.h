#pragma once
#include "common.h"

class SegmentTreeSum
{
private:
    int m_n;
    vector<int> m_dat;
public:
    void init(int n) {
        m_n = 1;
        while (m_n < n) m_n *= 2;
        m_dat.resize(2 * m_n - 1, 0);
    }
    // k番目に値valを加算
    void update(int k, int val) {
        k += m_n - 1;
        m_dat[k] += val;
        while (k > 0) {
            k = (k - 1) / 2;
            m_dat[k] = m_dat[k * 2 + 1] + m_dat[k * 2 + 2];
        }
    }
    // [a, b)の範囲で合計を返す
    int query(int a, int b) {
        return queryInternal(a, b, 0, 0, m_n);
    }

private:
    int queryInternal(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) return 0;
        if (a <= l && r <= b) return m_dat[k];
        else {
            int vl = queryInternal(a, b, k * 2 + 1, l, (l + r) / 2);
            int vr = queryInternal(a, b, k * 2 + 2, (l + r) / 2, r);
            return vl + vr;
        }
    }
};
