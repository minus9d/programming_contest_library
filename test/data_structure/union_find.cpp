#include "catch.hpp"
#include "data_structure/union_find.h"

TEST_CASE("union_find", "[data_structure]") {
    UnionFind uf;
    uf.init(5);
    uf.unite(3, 0);
    uf.unite(1, 2);
    uf.unite(4, 2);

    REQUIRE(uf.find(0) == uf.find(3));
    REQUIRE(uf.find(1) == uf.find(2));
    REQUIRE(uf.find(1) == uf.find(4));
    REQUIRE(uf.same(0, 3));
    REQUIRE(uf.same(1, 2));
    REQUIRE(uf.same(1, 4));
    REQUIRE(!uf.same(0, 1));
}
