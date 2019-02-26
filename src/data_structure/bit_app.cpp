#include "catch.hpp"
#include "data_structure/bit_app.h"

TEST_CASE("bubbleSortSwapNum", "[data_structure]") {
    REQUIRE(bubbleSortSwapNum<int>(vector<int>{3, 1, 4, 2}) == 3);
    REQUIRE(bubbleSortSwapNum<int>(vector<int>{1, 2, 3, 4}) == 0);
    REQUIRE(bubbleSortSwapNum<int>(vector<int>{4, 3, 2, 1}) == 6);
}

TEST_CASE("getNumberOfSegmentsWhoseSumIsNotNegative", "[data_structure]") {
    REQUIRE(getNumberOfSegmentsWhoseSumIsNotNegative<int>(vector<int>{-1, 1, -1}) == 3);
    REQUIRE(getNumberOfSegmentsWhoseSumIsNotNegative<int>(vector<int>{1, 1, 1}) == 6);
    REQUIRE(getNumberOfSegmentsWhoseSumIsNotNegative<int>(vector<int>{-1, -1, -1}) == 0);
}
