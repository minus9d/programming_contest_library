#include "catch.hpp"
#include "data_structure/segment_tree_sum.h"
#include "data_structure/segment_tree_min.h"

TEST_CASE("segment_tree_sum", "[data_structure]") {
    SegmentTreeSum st;
    st.init(8);
    st.update(4, 7);
    st.update(1, 2);
    REQUIRE(st.query(0, 8) == 9);
    REQUIRE(st.query(0, 4) == 2);
    st.update(2, 5);
    REQUIRE(st.query(0, 8) == 14);
}

TEST_CASE("segment_tree_min", "[data_structure]") {
    SegmentTreeMin st;
    st.init(8);
    st.update(0, 5);
    st.update(1, 2);
    st.update(2, 7);
    st.update(3, 1);
    st.update(4, -3);
    st.update(5, 4);
    st.update(6, 8);
    st.update(7, 2);
    REQUIRE(st.query(0, 8) == -3);
    REQUIRE(st.query(0, 4) == 1);
}
