#pragma once
#include "common.h"

// 出典: https://qiita.com/drken/items/ae02240cd1f8edfc86fd

// 負の数にも対応した mod
// 例えば -17 を 5 で割った余りは本当は 3 (-17 ≡ 3 (mod. 5))
// しかし単に -17 % 5 では -2 になってしまう
inline ll mod(ll a, ll m) {
    return (a % m + m) % m;
}

// 拡張 Euclid の互除法
// ap + bq = gcd(a, b) となる (p, q) を求め、d = gcd(a, b) をリターンします
ll extGcd(ll a, ll b, ll &p, ll &q) {  
    if (b == 0) { p = 1; q = 0; return a; }  
    ll d = extGcd(b, a%b, q, p);  
    q -= a/b * p;  
    return d;  
}

// 中国剰余定理
// リターン値を (r, m) とすると解は x ≡ r (mod. m)
// 解なしの場合は (0, -1) をリターン
// e.g. 3で割って2余り、5で割って3余る数を求めたいとき
//      すなわち x ≡ 2 (mod. 3) かつ x ≡ 3 (mod. 5) である xを求めたいとき
//      ChineseRem(2, 3, 3, 5) で (8, 15) が戻る。
//      これは、解が x ≡ 8 (mod. 15) であることを意味する
pair<ll, ll> chineseRemSimple(ll b1, ll m1, ll b2, ll m2) {
    ll p, q;
    ll d = extGcd(m1, m2, p, q); // p is inv of m1/d (mod. m2/d)
    if ((b2 - b1) % d != 0) return make_pair(0, -1);
    ll m = m1 * (m2/d); // lcm of (m1, m2)
    ll tmp = (b2 - b1) / d * p % (m2/d);
    ll r = mod(b1 + m1 * tmp, m);
    return make_pair(r, m);
}

// 中国剰余定理
// リターン値を (r, m) とすると解は x ≡ r (mod. m)
// 解なしの場合は (0, -1) をリターン
// verify: https://atcoder.jp/contests/abc150/tasks/abc150_d
pair<ll, ll> chineseRem(const vector<ll> &b, const vector<ll> &m) {
    ll r = 0, M = 1;
    for (int i = 0; i < (int)b.size(); ++i) {
        ll p, q;
        ll d = extGcd(M, m[i], p, q); // p is inv of M/d (mod. m[i]/d)
        if ((b[i] - r) % d != 0) return make_pair(0, -1);
        ll tmp = (b[i] - r) / d * p % (m[i]/d);
        r += M * tmp;
        M *= m[i]/d;
    }
    return make_pair(mod(r, M), M);
}

// 逆元計算 (ここでは a と m が互いに素であることが必要)
ll modinv(ll a, ll m) {
    ll x, y;
    extGcd(a, m, x, y);
    return mod(x, m); // 気持ち的には x % m だが、x が負かもしれないので
}

// Garner のアルゴリズム
//
// x ≡ b1 (mod. m1), x ≡ b2 (mod. m2), ..., x ≡ bK (mod. mK) を満たす
// 最小の 0 以上の整数 x を求める
// そして、x mod MOD の値を出力する
//
// m1, m2, ..., mKは互いに素でなければならない
//
// for each step, we solve "coeffs[k] * t[k] + constants[k] = b[k] (mod. m[k])"
//      coeffs[k] = m[0]m[1]...m[k-1]
//      constants[k] = t[0] + t[1]m[0] + ... + t[k-1]m[0]m[1]...m[k-2]
ll garner(vector<ll> b, vector<ll> m, ll MOD) {
    m.push_back(MOD); // banpei
    vector<ll> coeffs((int)m.size(), 1);
    vector<ll> constants((int)m.size(), 0);
    for (int k = 0; k < (int)b.size(); ++k) {
        ll t = mod((b[k] - constants[k]) * modinv(coeffs[k], m[k]), m[k]);
        for (int i = k+1; i < (int)m.size(); ++i) {
            (constants[i] += t * coeffs[i]) %= m[i];
            (coeffs[i] *= m[k]) %= m[i];
        }
    }
    return constants.back();
}
