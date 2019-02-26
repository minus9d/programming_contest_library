#pragma once
#include "common.h"
#include "bit.h"

// bit 応用

// Q. 1..Nを並び替えた長さNの配列がある。転倒数(=バブルソートの交換回数)を求めよ。
// 例: [3, 1, 4, 2]の転倒数は3
// 参考：プログラミングコンテストチャレンジブック 第一版 p162
// 注：値が飛び飛びの場合は事前に座標圧縮が必要
template <typename T>
ll bubbleSortSwapNum(const vector<int>& arr) {
    ll ans = 0;
    ll N = SIZE(arr);
    Bit bit; bit.init(N);
    REP(j, N) {
        ans += j - bit.sum(arr[j]);
        bit.add(arr[j], 1);
    }
    return ans;
}
