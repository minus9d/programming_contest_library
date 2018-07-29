#include "catch.hpp"
#include "data_structure/segment_tree_sum.h"
#include "data_structure/segment_tree_min_max.h"

TEST_CASE("segment_tree_sum", "[data_structure]") {
    SegmentTreeSum<int> st(8);
    st.update(4, 7);
    st.update(1, 2);
    REQUIRE(st.query(0, 8) == 9);
    REQUIRE(st.query(0, 4) == 2);
    st.update(2, 5);
    REQUIRE(st.query(0, 8) == 14);
}

TEST_CASE("segment_tree_min", "[data_structure]") {
    SegmentTreeMin<int> st(8);
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
    REQUIRE(st.query(2, 5) == -3);
}

TEST_CASE("segment_tree_max", "[data_structure]") {
    SegmentTreeMax<int> st(8);
    st.update(0, 5);
    st.update(1, 2);
    st.update(2, 7);
    st.update(3, 1);
    st.update(4, -3);
    st.update(5, 4);
    st.update(6, 8);
    st.update(7, 2);
    REQUIRE(st.query(0, 8) == 8);
    REQUIRE(st.query(0, 4) == 7);
    REQUIRE(st.query(2, 5) == 7);
}

TEST_CASE("segment_tree_min_with_index", "[data_structure]") {
    SegmentTreeMinWithIndex<int> st(8);
    st.update(0, 5);
    st.update(1, 2);
    st.update(2, 7);
    st.update(3, 1);
    st.update(4, -3);
    st.update(5, 4);
    st.update(6, 8);
    st.update(7, 2);
    REQUIRE(st.query(0, 8) == mp(-3, 4));
    REQUIRE(st.query(0, 4) == mp(1, 3));
}

TEST_CASE("segment_tree_max_with_index", "[data_structure]") {
    SegmentTreeMaxWithIndex<int> st(8);
    st.update(0, 5);
    st.update(1, 2);
    st.update(2, 7);
    st.update(3, 1);
    st.update(4, -3);
    st.update(5, 4);
    st.update(6, 8);
    st.update(7, 2);
    REQUIRE(st.query(0, 8) == mp(8, 6));
    REQUIRE(st.query(0, 4) == mp(7, 2));
}
