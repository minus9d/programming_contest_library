#pragma once
#include "common.h"

// verify: ABC121 D
// 0からnまでのXORを取った結果を返す
ll xor_to_n(ll n) {
    auto mod4 = n % 4;
    if (mod4 == 1) {
        return 1;
    } else if (mod4 == 3) {
        return 0;
    } else if (mod4 == 2) {
        return n ^ 1;
    } else {
        return n;
    }
}
