#pragma once
#include "common.h"

// 最大公約数
ll getGCD(ll a, ll b) {
    if (b == 0) return a;
    return getGCD(b, a % b);
}

// 最小公倍数
ll getLCM(ll a, ll b) {
    return a / getGCD(a, b) * b;
}
