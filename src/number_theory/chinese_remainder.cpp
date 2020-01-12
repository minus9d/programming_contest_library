#include "catch.hpp"
#include "number_theory/chinese_remainder.h"

TEST_CASE("chinseRemSimple", "[number_theory]") {
    // 3で割って2余り、5で割って3余る数は、15で割って8余る数
    REQUIRE(chineseRemSimple(2, 3, 3, 5) == mp(8LL, 15LL));
    // 4で割って1余り、6で割って2余る数は存在しない
    REQUIRE(chineseRemSimple(1, 4, 2, 6) == mp(0LL, -1LL));
}

TEST_CASE("chinseRem", "[number_theory]") {
    // 3で割って2余り、5で割って3余る数は、15で割って8余る数
    REQUIRE(chineseRem(vector<ll>{2, 3}, vector<ll>{3, 5}) == mp(8LL, 15LL));
    // 3で割って2余り、5で割って3余り、7で割って2余る数は、105で割って23余る数
    REQUIRE(chineseRem(vector<ll>{2, 3, 2}, vector<ll>{3, 5, 7}) == mp(23LL, 105LL));
    // 4で割って1余り、6で割って2余る数は存在しない
    REQUIRE(chineseRem(vector<ll>{1, 2}, vector<ll>{4, 6}) == mp(0LL, -1LL));
}

TEST_CASE("garner", "[number_theory]") {
}
