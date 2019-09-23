#pragma once
#include "common.h"

// 文字列が与えられた時、各 i について「SとS[i:]の最長共通接頭辞の長さ」をO(|S|)で構築
// e.g.
//   aaabaaaab
//   921034210
// reference: https://snuke.hatenablog.com/entry/2014/12/03/214243
// verify: https://atcoder.jp/contests/abc141/tasks/abc141_e
template <typename T>
vector<int> z_algorithm(T& s) {
    auto len = SIZE(s);
    vector<int> ret(len);
    ret[0] = len;
    int i = 1, j = 0;
    while (i < len) {
        while (i + j < len && s[j] == s[i+j]) ++j;
        ret[i] = j;
        if (j == 0) {++i; continue;}
        int k = 1;
        while (i + k < len && k + ret[k] < j) {ret[i+k] = ret[k]; ++k;}
        i += k; j -= k;
    }    
    return ret;
}
