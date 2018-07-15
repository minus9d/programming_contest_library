#include "catch.hpp"
#include "number_theory/gcd_and_lcm.h"

TEST_CASE("getGCD", "[number_theory]") {
    REQUIRE(getGCD(1, 1) == 1);
    REQUIRE(getGCD(1, 2) == 1);
    REQUIRE(getGCD(5, 7) == 1);
    REQUIRE(getGCD(900, 600) == 300);
}

TEST_CASE("getLCM", "[number_theory]") {
    REQUIRE(getLCM(1, 1) == 1);
    REQUIRE(getLCM(1, 2) == 2);
    REQUIRE(getLCM(5, 7) == 35);
    REQUIRE(getLCM(900, 600) == 1800);
}
