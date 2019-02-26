#include "catch.hpp"
#include "data_structure/bit.h"

TEST_CASE("bit", "[data_structure]") {
    Bit bit;
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
