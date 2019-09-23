#include "catch.hpp"
#include "string/rolling_hash.h"

TEST_CASE("single_rolling_hash", "[string]") {
    string str = "strangeorange";
    SingleRollingHash<string> rh_str(str);
    REQUIRE(rh_str.between(2, 7) == rh_str.between(8, 13));
    REQUIRE(rh_str.between(2, 7) != rh_str.between(8, 12));

    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 3, 4, 5, 6, 7};
    SingleRollingHash<vector<int>> rh_v(v);
    REQUIRE(rh_v.between(2, 7) == rh_v.between(8, 13));
    REQUIRE(rh_v.between(2, 7) != rh_v.between(8, 12));
}

TEST_CASE("multi_rolling_hash", "[string]") {
    string str = "strangeorange";
    MultiRollingHash<string> rh_str(str);
    REQUIRE(rh_str.between(2, 7) == rh_str.between(8, 13));
    REQUIRE(rh_str.between(2, 7) != rh_str.between(8, 12));

    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 3, 4, 5, 6, 7};
    MultiRollingHash<vector<int>> rh_v(v);
    REQUIRE(rh_v.between(2, 7) == rh_v.between(8, 13));
    REQUIRE(rh_v.between(2, 7) != rh_v.between(8, 12));
}
