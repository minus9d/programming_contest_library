#pragma once
#include "common.h"

// 文字列が与えられた時、各 i について
// 「文字 i を中心とする最長の回文の半径」を記録した配列 R を O(|S|) で構築
// e.g.
//   abaaababa
//   121412321
// reference: https://snuke.hatenablog.com/entry/2014/12/02/235837
// verify: None
template <typename T>
vector<int> manacher(T& s) {
    int i = 0;
    int j = 0;
    vector<int> R(SIZE(s));
    while (i < SIZE(s)) {
        while (i - j >= 0 && i + j < SIZE(s) && s[i - j] == s[i + j]) {
            ++j;
        }
        R[i] = j;
        int k = 1;
        while (i - k >= 0 && i + k < SIZE(s) && k + R[i - k] < j) {
            R[i + k] = R[i - k];
            ++k;
        }
        i += k;
        j -= k;
    }
    return R;
}
