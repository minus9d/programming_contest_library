#include "catch.hpp"
#include "number_theory/extgcd.h"

TEST_CASE("extgcd", "[number_theory]") {
    // ax + by == gcd(a, b) = 5を満たすx, yを求める。またgcd(a,b)を返す
    {
        ll a = 10;
        ll b = 15;
        ll x, y;
        auto gcd_val = extgcd(a, b, x, y);
        REQUIRE(gcd_val == 5LL);
        REQUIRE(a * x + b * y == gcd_val);
        // 本当は以下の2つには無限の候補あり
        REQUIRE(x == -1LL);
        REQUIRE(y == 1LL);
    }

    // 3x + 7y == 1を満たすx, yを求める。3と7が素数だから成り立つ問題
    {
        ll x, y;
        auto gcd_val = extgcd(3, 7, x, y);
        REQUIRE(gcd_val == 1LL);
        REQUIRE(3 * x + 7 * y == gcd_val);
        // 本当は以下の2つには無限の候補あり
        REQUIRE(x == -2LL);
        REQUIRE(y == 1LL);
    }
}
