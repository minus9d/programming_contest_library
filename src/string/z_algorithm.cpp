#include "catch.hpp"
#include "string/z_algorithm.h"

TEST_CASE("z_algorithm", "[string]") {
    vector<int> ans{9, 2, 1, 0, 3, 4, 2, 1, 0};

    string s = "aaabaaaab";
    REQUIRE(z_algorithm(s) == ans);

    vector<int> v{1, 1, 1, 2, 1, 1, 1, 1, 2};
    REQUIRE(z_algorithm(v) == ans);
}
