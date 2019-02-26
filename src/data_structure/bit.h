// BITの実装　数列の、最初の要素からある要素までの和を返す
// クラスとして実装
// 参考：プログラミングコンテストチャレンジブック 第一版 p161
// verify: http://arc075.contest.atcoder.jp/tasks/arc075_c

#pragma once
#include "common.h"

// 1 originなので注意!!
class Bit
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
