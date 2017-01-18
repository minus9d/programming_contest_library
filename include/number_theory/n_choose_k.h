#pragma once
#include "common.h"

class nCk {
private:
    ll m_mod;
    ll m_precompChooseMax = -1;
    ll m_precompModInverseMax = -1;

public:
    // mod must be a prime number
    nCk(ll mod) : m_mod(mod) {}

    vector<vector<ll>> m_chooseResult;
    vector<ll> m_modInverseResult;

    // x^y % m_mod
    ll modPow(ll x, ll y)
    {
        ll r = 1, a = x;
        while (y > 0) {
            if ((y&1) == 1) {
                r = (r * a) % m_mod;
            }
            a = (a * a) % m_mod;
            y /= 2;
        }
        return r;
    }

    // a^-1 ≡ a^(p-2) (mod p)   (p is prime)
    ll modInverse(ll x)
    {
        if (x <= m_precompModInverseMax) return m_modInverseResult[x];
        else return modPow(x, m_mod-2);
    }

    // Modular division x / y, find modular multiplicative inverse of y
    // and multiply by x.
    ll modDivision(ll p, ll q)
    {
        return (p * modInverse(q)) % m_mod;
    }

    // Binomial coifficient C(n,k) in O(k) time.
    ll choose(ll n, ll k)
    {
        if (max(n, k) <= m_precompChooseMax) {
            return m_chooseResult[n][k];
        }

        if (k > n) {
            return 0;
        }
        ll p = 1, q = 1;
        for (int i=1; i<=k; i++) {
            q = (q * i) % m_mod;
            p = (p * (n - i + 1)) % m_mod;
        }
        return modDivision(p, q);
    }

    // precompute nCk
    void precompChoose(ll n_max) {
        assert(n_max > 0);
        m_chooseResult.resize(n_max+1, vector<ll>(n_max+1));
        m_chooseResult[0][0] = 1;
        FOR(i, 1, n_max + 1) {
            m_chooseResult[i][0] = 1;
            FOR(j, 1, n_max + 1) {
                m_chooseResult[i][j]
                    = (m_chooseResult[i - 1][j - 1] + m_chooseResult[i - 1][j])
                    % m_mod;
            }
        }
        m_precompChooseMax = n_max;
    }
    // precompute modInverse
    void precompModInverse(ll n_max) {
        assert(n_max > 0);
        m_modInverseResult.resize(n_max + 1);
        FOR(i, 1, n_max + 1) {
            m_modInverseResult[i] = modInverse(i);
        }
        m_precompModInverseMax = n_max;
    }
};
