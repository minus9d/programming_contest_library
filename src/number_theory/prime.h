#pragma once
#include "common.h"

// 素数判定　遅いが通常これで十分
bool isPrime(ll n){
    if (n <= 1){
        return false;
    }
    for(int i = 2; i*i <= n; ++i){
        if (n % i == 0){
            return false;
        }
    }
    return true;
}

// n以下の素数を得る　遅いかも
vector<ll> getPrimesSlow(ll n) {
    vector<ll> primes;
    primes.clear();
    if (n < 2){
        return primes;
    }
    primes.push_back(2);
    if (n == 2){
        return primes;
    }
    primes.push_back(3);
    if (n == 3){
        return primes;
    }
    for(ll i = 5; i <= n; i += 2){
        bool isPrime = true;
        for(int p = 0; p < (int)primes.size(); ++p){
            if (i % primes[p] == 0){
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            primes.push_back(i);
        }
    }
    return primes;
}

// n以下の素数を得る　速い
// use Sieve of Eratosthenes
// warning: needs lots of memory
vector<ll> getPrimesFast(ll n){
    vector<ll> primes;
    if (n < 10000){
        primes.clear();
        if (n < 2){
            return primes;
        }
        primes.push_back(2);
        if (n == 2){
            return primes;
        }
        primes.push_back(3);
        if (n == 3){
            return primes;
        }
        for(ll i = 5; i <= n; i += 2){
            bool isPrime = true;
            for(int p = 0; p < (int)primes.size(); ++p){
                if (i % primes[p] == 0){
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) {
                primes.push_back(i);
            }
        }
        return primes;
    }
    else{
        vector<ll> sieve = getPrimesFast(sqrt(n));

        vector<short> isPrime(n+1, 1);
        for(int i = 0; i < (int)sieve.size(); ++i){
            for(int j = sieve[i] * 2; j <= n; j += sieve[i]){
                isPrime[j] = 0;
            }
        }

        for(int i = 2; i <= n; ++i){
            if (isPrime[i]){
                primes.push_back(i);
            }
        }
        return primes;
    }
}

// 素数をn個作る
vector<ll> getFirstNPrimes(int n) {
    vector<ll> primes;

    if (n < 1){
        return primes;
    }
    primes.push_back(2);
    if (n == 1){
        return primes;
    }
    primes.push_back(3);
    if (n == 2){
        return primes;
    }
    int num = 2;
    for(ll i = 5; num < n; i += 2){
        bool isPrime = true;
        for(int p = 0; p < (int)primes.size(); ++p){
            if (i % primes[p] == 0){
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            primes.push_back(i);
            ++num;
        }
    }
    return primes;
}

// nの約数を得る
// n=12に対して1, 2, 3, 4, 6, 12を返す
// fast, including 1
set<ll> getDivisorsSet(ll n){
    set<ll> ret;
    for(ll i = 1; i*i <= n; ++i){
        if (!(n % i)){
            ret.insert(i);
            ret.insert(n/i);
        }
    }
    return ret;
}

// nの素因数を得る（回数はカウントしない）
// n=12に対して2, 3を返す
set<ll> getFactorsSet(ll n){
    if (n == 0) return set<ll>{};

    set<ll> ret;
    while(!(n % 2)){
        n /= 2;
        ret.insert(2);
    }
    ll orig_n = n;
    for(ll i = 3; i * i <= orig_n; i += 2){
        while(!(n % i)){
            n /= i;
            ret.insert(i);
        }
    }
    if (n != 1) ret.insert(n);
    return ret;
}

// nを素数の積で表す
// e.g. n=12に対して2, 2, 3を返す
vector<ll> getFactorsVector(ll n){
    if (n == 0) return vector<ll>{};

    vector<ll> ret;
    while(!(n % 2)){
        n /= 2;
        ret.push_back(2);
    }
    for(int i = 3; i*i <= n; i += 2){
        while(!(n % i)){
            n /= i;
            ret.push_back(i);
        }
    }
    if (n > 1) ret.push_back(n);
    return ret;
}

// verify
// Nを素因数分解して、<素因数, 登場回数>のペアを得る
// N=12に対して <2, 2>, <3, 1>を得る
map<ll, int> getFactorsMap(ll N){
    map<ll, int> ret;
    while(!(N % 2)){
        N /= 2;
        ++ret[2];
    }
    for (ll p = 3; p*p <= N; p += 2) {
        while (N % p == 0) {
            N /= p;
            ++ret[p];
        }
    }
    if (N > 1) ++ret[N];
    return ret;
}

// 2数の最大公約数
ll getGcdSimple(ll a, ll b)
{
    if (b == 0) return a;
    return getGcdSimple(b, a % b);
}

// 2数の最小公倍数
ll getLcmSimple(ll a, ll b)
{
    return a / getGcdSimple(a, b) * b;
}

// 数のリストから最大公約数を求める
ll getGcd(vector<ll> n){
    auto size = SIZE(n);
    assert(size > 0);
    ll ans = n[0];
    FOR(i, 1, size) ans = getGcdSimple(ans, n[i]);
    return ans;
}

// 数のリストからleast common multiple(最小公倍数)を求める
ll getLcm(vector<ll> n){
    map<ll, int> allFactors;
    for(int i = 0; i < (int)n.size(); ++i){
        map<ll, int> factors = getFactorsMap(n[i]);
        for(map<ll, int>::iterator it = factors.begin();
            it != factors.end();
            ++it){
            if (allFactors[ it->first ] < it->second){
                allFactors[ it->first ] = it->second;
            }
        }
    }
    ll ret = 1;
    for(map<ll, int>::iterator it = allFactors.begin();
        it != allFactors.end();
        ++it){
        for(int i = 0; i < it->second; ++i){
            ret *= it->first;
        }
    }
    return ret;
}

// 約数の数を得る  e.g. 12 -> 6 (1, 2, 3, 4, 6, 12の6個)
ll getDivisorsNum(ll n){
    map<ll, int> factors = getFactorsMap(n);
    ll ret = 1;
    for(auto kv: factors) {
        ret *= kv.second + 1;
    }
    return ret;
}

// 約数のリストを得る　遅いかも
vector<ll> getAllDivisors(ll n){
    vector<ll> ret;
    for(ll i = 1; i*i <= n; ++i){
        if (n % i == 0){
            ret.push_back(i);
            if (i != n/i){
                ret.push_back(n/i);
            }
        }
    }
    sort(ALL(ret));
    return ret;
}
