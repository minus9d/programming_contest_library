#include "catch.hpp"
#include "data_structure/bit.h"

TEST_CASE("bit", "[data_structure]") {
    BitSimple bit;
    int N = 8;
    bit.init(N);
    for(int i = 0; i < N; ++i) {
        bit.add(i + 1, i + 1);
    }
    REQUIRE(bit.sum(0) == 0);
    REQUIRE(bit.sum(1) == 1);
    REQUIRE(bit.sum(2) == 3);
    REQUIRE(bit.sum(3) == 6);
    REQUIRE(bit.sum(4) == 10);
    REQUIRE(bit.sum(5) == 15);
    REQUIRE(bit.sum(6) == 21);
    REQUIRE(bit.sum(7) == 28);
    REQUIRE(bit.sum(8) == 36);
}

// drken氏のBIT (区間加算対応版)
TEST_CASE("bit_drken_1", "[data_structure]") {
    const int N = 8;
    BIT<ll> bit(N);

    // 1番目に1, 2番目に2, ...を加算
    for(int i = 0; i < N; ++i) {
        bit.add(i + 1, i + 2, i + 1);
    }
    // 1番目
    REQUIRE(bit.sum(1, 2) == 1);
    // 1番目~2番目の和
    REQUIRE(bit.sum(1, 3) == 3);
    REQUIRE(bit.sum(1, 4) == 6);
    REQUIRE(bit.sum(1, 5) == 10);
    REQUIRE(bit.sum(1, 6) == 15);
    REQUIRE(bit.sum(1, 7) == 21);
    REQUIRE(bit.sum(1, 8) == 28);
    REQUIRE(bit.sum(1, 9) == 36);
}

// drken氏のBIT (区間加算対応版)
TEST_CASE("bit_drken_2", "[data_structure]") {
    const int N = 8;
    BIT<ll> bit(N);

    // 1番目~4番目に +2
    // 3番目~7番目に +5
    // 6番目~8番目に -1
    // 結果、2 2 7 7 5 4 4 -1 となるはず
    bit.add(1, 5, +2);
    bit.add(3, 8, +5);
    bit.add(6, 9, -1);

    // 1番目
    REQUIRE(bit.sum(1, 2) == 2);
    // 2番目
    REQUIRE(bit.sum(2, 3) == 2);
    REQUIRE(bit.sum(3, 4) == 7);
    REQUIRE(bit.sum(4, 5) == 7);
    REQUIRE(bit.sum(5, 6) == 5);
    REQUIRE(bit.sum(6, 7) == 4);
    REQUIRE(bit.sum(7, 8) == 4);
    REQUIRE(bit.sum(8, 9) == -1);

    // 1番目
    REQUIRE(bit.sum(1, 2) == 2);
    // 1番目~2番目の和
    REQUIRE(bit.sum(1, 3) == 4);
    REQUIRE(bit.sum(1, 4) == 11);
    REQUIRE(bit.sum(1, 5) == 18);
    REQUIRE(bit.sum(1, 6) == 23);
    REQUIRE(bit.sum(1, 7) == 27);
    REQUIRE(bit.sum(1, 8) == 31);
    REQUIRE(bit.sum(1, 9) == 30);
}
