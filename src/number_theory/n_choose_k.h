#pragma once
#include "common.h"

class NCK {
private:
    ll m_mod;

public:
    // mod must be a prime number
    NCK(ll mod) : m_mod(mod) {}

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
        return modPow(x, m_mod-2);
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

    // make nCk table from 0C0 to nCn
    vector<vector<ll>> makeNckTableFrom00ToNN(ll n_max) {
        assert(n_max > 0);
        vector<vector<ll>> table(n_max+1, vector<ll>(n_max+1));
        table[0][0] = 1;
        FOR(i, 1, n_max + 1) {
            table[i][0] = 1;
            FOR(j, 1, n_max + 1) {
                table[i][j] = (table[i - 1][j - 1] + table[i - 1][j]) % m_mod;
            }
        }
        return table;
    }

    // make nCk table from nC0 to nCn
    vector<ll> makeNckTableFromN0ToNN(ll n, ll k_max) {
        assert(n > 0);
        assert(n >= k_max);
        vector<ll> table(n+1);
        table[0] = 1;
        ll p = 1, q = 1;
        table[0] = 1;
        FOR(i, 1, k_max+1) {
            q = (q * i) % m_mod;
            p = (p * (n - i + 1)) % m_mod;
            table[i] = modDivision(p, q);
        }
        return table;
    }

    // make nCk table from n1Ck to n2Ck
    vector<ll> makeTableFromN1CkToN2Ck(ll n1, ll n2, ll k) {
        vector<ll> table;

        // n < kのときは nCk = 0
        FOR(n, n1, k) {
            table.pb(0);
        }

        ll tmp = -1;
        FOR(n, k, n2 + 1) {
            if (n == k) {
                tmp = this->choose(n, k);
            }
            else {
                tmp *= n;
                tmp %= this->m_mod;
                tmp = this->modDivision(tmp, n - k);
            }
            table.pb(tmp);
        }
        return table;
    }

    // make modInverse table from 0 to n_max
    vector<ll> makeModInverseTable(ll n_max) {
        assert(n_max > 0);
        vector<ll> table(n_max + 1);
        FOR(i, 1, n_max + 1) {
            table[i] = modInverse(i);
        }
        return table;
    }
};
