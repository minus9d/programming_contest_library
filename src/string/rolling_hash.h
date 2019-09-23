#pragma once
#include "common.h"

// ローリングハッシュを生成するクラス
// string strに対してはSingleRollingHash<string>(str),
// vector<int> vに対してはSingleRollingHash<vector<int>>(v) などと使う
// ハッシュ値の衝突を避けるため、MultiRollingHashの使用を推奨
// reference: https://betrue12.hateblo.jp/entry/2019/09/16/013915
// verify: https://atcoder.jp/contests/abc141/tasks/abc141_e
template <typename T>
class SingleRollingHash{
private:
    vector<int64_t> m_hash;
    vector<int64_t> m_base_pow;
    int64_t m_base, m_mod;
    const int64_t DEFAULT_BASE = 1009, DEFAULT_MOD = 1e9+7;
    void initialize(T& S){
        m_hash.resize(SIZE(S) + 1);
        m_base_pow.resize(SIZE(S) + 1);
        m_hash[0] = 0;
        m_base_pow[0] = 1;
        FOR(i, 1, SIZE(S) + 1) {
            m_hash[i] = (m_hash[i - 1] * m_base + S[i - 1]) % m_mod;
            m_base_pow[i] = m_base_pow[i - 1] * m_base % m_mod;
        }
    }
public:
    SingleRollingHash(T& S, int64_t base_ = -1, int64_t mod_ = -1){
        m_base = base_ > 0 ? base_ : DEFAULT_BASE;
        m_mod = mod_ > 0 ? mod_ : DEFAULT_MOD;
        if(SIZE(S) > 0) initialize(S);
    }

    // 0-indexed, [a, b)
    int64_t between(int a, int b){
        return (m_mod + m_hash[b] - m_hash[a] * m_base_pow[b-a] % m_mod) % m_mod;
    }
 
};

using Hashed = vector<int64_t>;

// 複数のローリングハッシュを用いて頑健性向上
template <typename T>
class MultiRollingHash{
private:
    vector<SingleRollingHash<T>> m_rolling_hash_list;
public:
    MultiRollingHash(T& S) {
        m_rolling_hash_list.emplace_back(SingleRollingHash<T>(S, 1007, 1e9+7));
        m_rolling_hash_list.emplace_back(SingleRollingHash<T>(S, 2009, 1e9+9));
    }

    // 0-indexed, [a, b)
    Hashed between(int a, int b){
        Hashed ret;
        for(auto& rh: m_rolling_hash_list) {
            ret.emplace_back(rh.between(a, b));
        }
        return ret;
    }
};
