#pragma once
#include "common.h"

// extgcd
// ax + by = gcd(a, b)の解(x, y)を求める。また、gcd(a, b)の値をreturnで返す。
// 参考：プログラミングコンテストチャレンジブック 第一版 p119
//
// 例えば, 「a * x + b * y = 1となる整数x, yを求めよ」などという問題を解くのに使える。
// これはaとbが互いに素なときしか解がない
// 
ll extgcd(ll a, ll b, ll& x, ll& y) {
    ll d = a;
    if (b != 0) {
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }
    else {
        x = 1;
        y = 0;
    }
    return d;
}
