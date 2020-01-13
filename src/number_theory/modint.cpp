#include "catch.hpp"
#include "number_theory/modint.h"

TEST_CASE("modint", "[number_theory]") {
    constexpr ll MOD = 5;
    using modint = Fp<MOD>;

    REQUIRE(modint(6) == modint(1));
    REQUIRE(modint(-4) == modint(1));

    modint a = 2;
    a += 6;
    REQUIRE(a == 3);
    a -= 4;
    REQUIRE(a == 4);
    a *= 3;
    REQUIRE(a == 2);
    a /= 4;
    REQUIRE(a == 3);
}
