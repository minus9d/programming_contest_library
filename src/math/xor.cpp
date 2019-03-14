#include "catch.hpp"
#include "math/xor.h"

TEST_CASE("xor", "[math]") {
    ll result = 0;
    REP(i, 16) {
        result ^= i;
        REQUIRE(result == xor_to_n(i));
    }
}
