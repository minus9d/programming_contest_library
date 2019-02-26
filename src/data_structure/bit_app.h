#pragma once
#include "common.h"
#include "bit.h"

// bit 応用

// Q. 長さNの配列がある。連続する部分配列N(N+1)/2通りのうち、
//    その和が0以上であるものの個数を求めよ
// 例: 配列が[-1, 1, -1] の場合, 3個
// 参考: https://atcoder.jp/contests/arc101/tasks/arc101_b
//      区間[l, r]の和が0以上であることと、S_r - S_{l-1} >= 0 は同値なのを利用
//      後者は転倒数と同様に、累積和をうまく使って計算可能。
//      BITを使うためには全要素が1以上であることが必要なため下駄を履かせる
//
//      例えば配列が[-1, 1, -1]の場合
//      累積和は    [-1, 0, -1]。
//      頭に0を入れると計算しやすいので入れて[0, -1, 0, -1]
//      ここで 全体に+2だけ下駄を履かせて [2, 1, 2, 1]
//      あとは、2番目の要素から順に、「自分より左にある要素のうち
//      自分以下の要素の数」を足せばよい

template <typename T>
ll getNumberOfSegmentsWhoseSumIsNotNegative(const vector<T>& arr) {
    auto N = SIZE(arr);
    // まず累積和作成  のちの計算を簡単にするため先頭に0を入れる
    vector<T> cum(N+1);
    REP(i, N) cum[i + 1] += cum[i] + arr[i];

    // BITを使うため最小値を1に
    auto mn = *min_element(ALL(cum));
    auto offset = -mn + 1;
    for(auto& e: cum) e += offset;
    auto mx = *max_element(ALL(cum));

    ll ans = 0;
    Bit bit; bit.init(mx);
    bit.add(offset, 1);
    FOR(i, 1, N + 1) {
        auto c = cum[i];
        ans += bit.sum(c);
        bit.add(c, 1);
    }
    return ans;
}

// Q. 1..Nを並び替えた長さNの配列がある。転倒数(=バブルソートの交換回数)を求めよ。
// 例: [3, 1, 4, 2]の転倒数は3
// 参考：プログラミングコンテストチャレンジブック 第一版 p162
// 注：値が飛び飛びの場合は事前に座標圧縮が必要
template <typename T>
ll bubbleSortSwapNum(const vector<T>& arr) {
    ll ans = 0;
    ll N = SIZE(arr);
    Bit bit; bit.init(N);
    REP(j, N) {
        ans += j - bit.sum(arr[j]);
        bit.add(arr[j], 1);
    }
    return ans;
}
