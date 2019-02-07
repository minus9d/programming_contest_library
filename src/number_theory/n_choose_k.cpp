#include "catch.hpp"
#include "number_theory/n_choose_k.h"

TEST_CASE("modPow", "[number_theory]") {
    // これに関しては mod は素数でなくてよい
    NCK nck(50);
    REQUIRE(nck.modPow(1, 0) == 1);
    REQUIRE(nck.modPow(1, 1) == 1);
    REQUIRE(nck.modPow(2, 10) == 24); // 2^10 mod 50 
}

TEST_CASE("modInverse", "[number_theory]") {
    NCK nck(7); // mod は素数である必要あり
    REQUIRE(nck.modInverse(0) == 0); // 0^(7-2)
    REQUIRE(nck.modInverse(1) == 1); // 1^(7-2)
    REQUIRE(nck.modInverse(2) == 4); // 2^(7-2)
    REQUIRE(nck.modInverse(3) == 5); // 3^(7-2) = 243
    REQUIRE(nck.modInverse(4) == 2); // 4^(7-2) = 1024
    REQUIRE(nck.modInverse(5) == 3); // 5^(7-2) = 3125
    REQUIRE(nck.modInverse(6) == 6); // 6^(7-2) = 7776
    REQUIRE(nck.modInverse(7) == 0); // 7^(7-2)
    // 以下ループ
}

TEST_CASE("modDivision", "[number_theory]") {
    NCK nck(7);
    REQUIRE(nck.modDivision(5, 2) == 6);
    REQUIRE(nck.modDivision(5, 3) == 4);
}


TEST_CASE("choose", "[number_theory]") {
    NCK nck(1e9 + 7);
    REQUIRE(nck.choose(0, 0) == 1);
    REQUIRE(nck.choose(1, 0) == 1);
    REQUIRE(nck.choose(1, 1) == 1);
    REQUIRE(nck.choose(7, 2) == 21);
    REQUIRE(nck.choose(1000, 456) == 852866745);
}

TEST_CASE("makeNckTableFrom00ToNN", "[number_theory]") {
    NCK nck(1e9 + 7);
    auto table = nck.makeNckTableFrom00ToNN(7);
    REQUIRE(table[0][0] == 1);
    REQUIRE(table[1][0] == 1);
    REQUIRE(table[1][1] == 1);
    REQUIRE(table[7][2] == 21);
}

TEST_CASE("makeNckTableFromN0ToNN", "[number_theory]") {
    NCK nck(1e9 + 7);
    auto table = nck.makeNckTableFromN0ToNN(7, 7);
    REQUIRE(table[0] == 1);
    REQUIRE(table[1] == 7);
    REQUIRE(table[2] == 21);
    REQUIRE(table[7] == 1);
}

TEST_CASE("makeTableFromN1CkToN2Ck", "[number_theory]") {
    NCK nck(1e9 + 7);
    auto table = nck.makeTableFromN1CkToN2Ck(2, 7, 2);
    REQUIRE(table[0] == 1);  // 2C2
    REQUIRE(table[1] == 3);  // 3C2
    REQUIRE(table[2] == 6);  // 4C2
    REQUIRE(table[3] == 10);  // 5C2
    REQUIRE(table[4] == 15);  // 6C2
    REQUIRE(table[5] == 21);  // 7C2
}

TEST_CASE("makeModInverseTable", "[number_theory]") {
    NCK nck(7);
    auto table = nck.makeModInverseTable(7);
    NCK nck2(7);
    REP(i, 7 + 1) {
        REQUIRE(table[i] == nck2.modInverse(i));
    }
}
