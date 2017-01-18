#include "catch.hpp"
#include "number_theory/n_choose_k.h"

TEST_CASE("modPow", "[number_theory]") {
    nCk nck(50);
    REQUIRE(nck.modPow(1, 0) == 1);
    REQUIRE(nck.modPow(1, 1) == 1);
    REQUIRE(nck.modPow(2, 10) == 24);
}

TEST_CASE("choose", "[number_theory]") {
    nCk nck(1e9 + 7);
    REQUIRE(nck.choose(0, 0) == 1);
    REQUIRE(nck.choose(1, 0) == 1);
    REQUIRE(nck.choose(1, 1) == 1);
    REQUIRE(nck.choose(7, 2) == 21);
    REQUIRE(nck.choose(1000, 456) == 852866745);
}
