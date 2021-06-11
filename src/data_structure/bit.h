// BITの実装　数列の、最初の要素からある要素までの和を返す
// クラスとして実装
// 参考：プログラミングコンテストチャレンジブック 第一版 p161
// verify: http://arc075.contest.atcoder.jp/tasks/arc075_c

#pragma once
#include "common.h"

// 区間加算に対応しないBIT (1-based)
class BitSimple
{
private:
    int m_n;
    vector<int> m_bit;
    
public:
    void init(int n) {
        m_n = n;
        m_bit.resize(n + 1);
    }

    // 要素1から要素iまでの和
    int sum(int i) {
        int s = 0;
        while (i > 0) {
            s += m_bit[i];
            i -= i & -i;
        }
        return s;
    }
    
    void add(int i, int x) {
        while (i <= m_n) {
            m_bit[i] += x;
            i += i & -i;
        }
    }
};

// https://github.com/drken1215/algorithm/blob/master/DataStructure/binary_indexed_tree.cpp
// 区間加算にも対応した BIT (1-based)
// 参考: https://www.slideshare.net/hcpc_hokudai/binary-indexed-tree
template <class Abel> struct BIT {
    vector<Abel> dat[2];
    Abel UNITY_SUM = 0;                     // to be set
    
    /* [1, n] */
    BIT(int n) { init(n); }
    void init(int n) {
        REP(iter, 2) dat[iter].assign(n + 1, UNITY_SUM);
    }
    
    // 区間[a, b)に値xを加算
    inline void add(int a, int b, Abel x) {
        sub_add(0, a, x * -(a - 1)); sub_add(1, a, x); sub_add(0, b, x * (b - 1)); sub_add(1, b, x * (-1));
    }

    // 区間[a, b)の和を返す
    inline Abel sum(int a, int b) {
        return sub_sum(0, b - 1) + sub_sum(1, b - 1) * (b - 1) - sub_sum(0, a - 1) - sub_sum(1, a - 1) * (a - 1);
    }

    /* debug */
    void print() {
        for (int i = 1; i < (int)dat[0].size(); ++i) cout << sum(i, i + 1) << ",";
        cout << endl;
    }

private:
    inline void sub_add(int p, int a, Abel x) {
        for (int i = a; i < (int)dat[p].size(); i += i & -i)
            dat[p][i] = dat[p][i] + x;
    }

    inline Abel sub_sum(int p, int a) {
        Abel res = UNITY_SUM;
        for (int i = a; i > 0; i -= i & -i) res = res + dat[p][i];
        return res;
    }
};
