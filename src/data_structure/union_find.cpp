#include "catch.hpp"
#include "data_structure/union_find.h"

TEST_CASE("union_find", "[data_structure]") {
    UnionFind uf;
    uf.init(5);
    for(int i = 0; i < 5; ++i) {
        REQUIRE(uf.size(i) == 1);
    }

    uf.unite(3, 0);
    REQUIRE(uf.find(0) == uf.find(3));
    REQUIRE(uf.same(0, 3));
    REQUIRE(uf.size(0) == 2);
    REQUIRE(uf.size(3) == 2);

    uf.unite(1, 2);
    REQUIRE(uf.find(1) == uf.find(2));
    REQUIRE(uf.same(1, 2));
    REQUIRE(uf.size(1) == 2);
    REQUIRE(uf.size(2) == 2);

    uf.unite(4, 2);
    REQUIRE(uf.find(1) == uf.find(4));
    REQUIRE(uf.same(1, 4));
    REQUIRE(!uf.same(0, 1));
    REQUIRE(uf.size(1) == 3);
    REQUIRE(uf.size(2) == 3);
    REQUIRE(uf.size(4) == 3);

    uf.unite(3, 1);
    for(int i = 0; i < 5; ++i) {
        REQUIRE(uf.find(0) == uf.find(i));
        REQUIRE(uf.same(0, i));
        REQUIRE(uf.size(i) == 5);
    }
}
