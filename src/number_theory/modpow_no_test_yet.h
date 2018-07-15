#pragma once
#include "common.h"

// 繰り返し二乗法
// 参考：プログラミングコンテストチャレンジブック 第一版 p126

// 繰り返し二乗法
// x ^ n % modを求める
ll mod_pow(ll x, ll n, ll mod) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

// 繰り返し二乗法の別実装
ll mod_pow_alt(ll x, ll n, ll mod) {
    if (n == 0) return 1;
    ll res = mod_pow_alt(x * x % mod, n / 2, mod);
    if (n & 1) res = res * x % mod;
    return res;
}

int main(){
    assert(mod_pow(3, 5, 1000) == 243);
    assert(mod_pow(3, 5, 100) == 43);
    return 0;
}
