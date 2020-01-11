#include "catch.hpp"
#include "data_structure/cumulative_sum.h"

TEST_CASE("CumSum1D", "[data_structure]") {
    vector<int> arr{3, -2, 5, 1, -7};
    CumSum1D<int> cumSum;
    cumSum.init(arr);
    REQUIRE(cumSum.getSum(0, 0) == 3);
    REQUIRE(cumSum.getSum(0, 1) == 1);
    REQUIRE(cumSum.getSum(0, 4) == 0);
    REQUIRE(cumSum.getSum(3, 4) == -6);
    REQUIRE(cumSum.getSum(4, 4) == -7);
}

TEST_CASE("CumSum2D", "[data_structure]") {
    vector<vector<int>> arr{
        {3, -2, 5, 1},
        {1, -4, 7, -2},
        {-2, 0, 1, 3}
    };
    CumSum2D<int> cumSum;
    cumSum.init(arr);
    REQUIRE(cumSum.getSum(0, 0, 0, 0) == 3);
    REQUIRE(cumSum.getSum(0, 0, 1, 0) == 1);
    REQUIRE(cumSum.getSum(0, 0, 0, 1) == 4);
    REQUIRE(cumSum.getSum(0, 0, 1, 1) == -2);

    REQUIRE(cumSum.getSum(3, 2, 3, 2) == 3);
    REQUIRE(cumSum.getSum(2, 2, 3, 2) == 4);
    REQUIRE(cumSum.getSum(3, 1, 3, 2) == 1);
    REQUIRE(cumSum.getSum(2, 1, 3, 2) == 9);

    REQUIRE(cumSum.getSum(1, 1, 2, 1) == 3);
}
