#include "catch.hpp"
#include "string/manacher.h"

TEST_CASE("manacher", "[string]") {
    vector<int> ans{1, 2, 1, 4, 1, 2, 3, 2, 1};

    string s = "abaaababa";
    REQUIRE(manacher(s) == ans);

    vector<int> v{1, 2, 1, 1, 1, 2, 1, 2, 1};
    REQUIRE(manacher(v) == ans);
}
