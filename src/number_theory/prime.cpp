#include "catch.hpp"
#include "number_theory/prime.h"

TEST_CASE("isPrime", "[number_theory]") {
    REQUIRE(isPrime(1) == false);
    REQUIRE(isPrime(2) == true);
    REQUIRE(isPrime(3) == true);
    REQUIRE(isPrime(4) == false);
    REQUIRE(isPrime(5) == true);
    REQUIRE(isPrime(100) == false);
}

TEST_CASE("getPrimesFast", "[number_theory]") {
    vector<ll> exp1;
    vector<ll> exp2{2};
    vector<ll> exp3{2, 3};
    vector<ll> exp13{2, 3, 5, 7, 11, 13};

    REQUIRE(getPrimesFast(1) == exp1);
    REQUIRE(getPrimesFast(2) == exp2);
    REQUIRE(getPrimesFast(3) == exp3);
    REQUIRE(getPrimesFast(13) == exp13);
    REQUIRE(getPrimesSlow(1) == exp1);
    REQUIRE(getPrimesSlow(2) == exp2);
    REQUIRE(getPrimesSlow(3) == exp3);
    REQUIRE(getPrimesSlow(13) == exp13);
    REQUIRE(getPrimesFast(10000) == getPrimesSlow(10000));
    REQUIRE(getPrimesFast(300000) == getPrimesSlow(300000));
}

TEST_CASE("getFirstNPrimes", "[number_theory]") {
    vector<ll> exp1{2};
    vector<ll> exp2{2, 3};
    vector<ll> exp6{2, 3, 5, 7, 11, 13};
    REQUIRE(getFirstNPrimes(1) == (vector<ll>{2}));
    REQUIRE(getFirstNPrimes(2) == (vector<ll>{2, 3}));
    REQUIRE(getFirstNPrimes(6) == (vector<ll>{2, 3, 5, 7, 11, 13}));
}

TEST_CASE("getDivisorsSet", "[number_theory]") {
    REQUIRE(getDivisorsSet(1) == (set<ll>{1}));
    REQUIRE(getDivisorsSet(2) == (set<ll>{1, 2}));
    REQUIRE(getDivisorsSet(12) == (set<ll>{1, 2, 3, 4, 6, 12}));
}

TEST_CASE("getFactorsVector", "[number_theory]") {
    REQUIRE(getFactorsVector(1) == (vector<ll>{}));
    REQUIRE(getFactorsVector(2) == (vector<ll>{2}));
    REQUIRE(getFactorsVector(12) == (vector<ll>{2, 2, 3}));
    REQUIRE(getFactorsVector(32) == (vector<ll>{2, 2, 2, 2, 2}));
    REQUIRE(getFactorsVector(100) == (vector<ll>{2, 2, 5, 5}));
    REQUIRE(getFactorsVector(121) == (vector<ll>{11, 11}));
    REQUIRE(getFactorsVector(143) == (vector<ll>{11, 13}));
    REQUIRE(getFactorsVector(2196095973992233039) == 
            (vector<ll>{1299817, 1299821, 1299827}));
    REQUIRE(getFactorsVector(1000007850015405589) ==
            (vector<ll>{1000003919,	1000003931}));
}

TEST_CASE("getFactorsMap", "[number_theory]") {
    map<ll, int> empty;
    REQUIRE(getFactorsMap(1) == empty);
    REQUIRE(getFactorsMap(2) == (map<ll, int>{{2, 1}}));
    REQUIRE(getFactorsMap(12) == (map<ll, int>{{2, 2}, {3, 1}}));
    REQUIRE(getFactorsMap(32) == (map<ll, int>{{2, 5}}));
    REQUIRE(getFactorsMap(100) == (map<ll, int>{{2, 2}, {5, 2}}));

    REQUIRE(getFactorsMap(121) == (map<ll, int>{{11, 2}}));
    REQUIRE(getFactorsMap(143) == (map<ll, int>{{11, 1}, {13, 1}}));
    REQUIRE(getFactorsMap(2196095973992233039) == 
            (map<ll, int>{{1299817, 1}, {1299821, 1}, {1299827, 1}}));
    REQUIRE(getFactorsMap(1000007850015405589) ==
            (map<ll, int>{{1000003919, 1}, {1000003931, 1}}));
}
// 2数の最大公約数
TEST_CASE("getGcdSimple", "[number_theory]") {
    REQUIRE(getGcdSimple(1, 1) == 1);
    REQUIRE(getGcdSimple(1, 2) == 1);
    REQUIRE(getGcdSimple(3, 5) == 1);
    REQUIRE(getGcdSimple(30, 45) == 15);
}

// 2数の最小公倍数
TEST_CASE("getLcmSimple", "[number_theory]") {
    REQUIRE(getLcmSimple(1, 1) == 1);
    REQUIRE(getLcmSimple(1, 2) == 2);
    REQUIRE(getLcmSimple(3, 5) == 15);
    REQUIRE(getLcmSimple(30, 45) == 90);
    REQUIRE(getLcmSimple(8, 12) == 24);
}

// 最大公約数
TEST_CASE("getGcd", "[number_theory]") {
    REQUIRE((getGcd(vector<ll>{1})) == 1);
    REQUIRE((getGcd(vector<ll>{8, 12})) == 4);
    // 2*3*5, 2*5*7, 2*5*11 -> 2*5
    REQUIRE((getGcd(vector<ll>{30, 70, 110})) == 10);
}

// 最小公倍数
TEST_CASE("getLcm", "[number_theory]") {
    REQUIRE((getLcm(vector<ll>{1})) == 1);
    REQUIRE((getLcm(vector<ll>{8, 12})) == 24);
    // 2*3, 2*5, 3*7 -> 2*3*5*7
    REQUIRE((getLcm(vector<ll>{6, 10, 21})) == 210);
}

// 約数の数を得る
TEST_CASE("getDivisorsNum", "[number_theory]") {
    REQUIRE(getDivisorsNum(1) == 1);
    REQUIRE(getDivisorsNum(2) == 2);
    REQUIRE(getDivisorsNum(12) == 6);
}

// 約数のリストを得る
TEST_CASE("getAllDivisors", "[number_theory]") {
    REQUIRE(getAllDivisors(1) == (vector<ll>{1}));
    REQUIRE(getAllDivisors(2) == (vector<ll>{1, 2}));
    REQUIRE(getAllDivisors(12) == (vector<ll>{1, 2, 3, 4, 6, 12}));
}
