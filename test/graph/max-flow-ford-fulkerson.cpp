#include "catch.hpp"
#include "graph/max-flow-ford-fulkerson.h"

TEST_CASE("ford-fulkerson", "[graph]") {
    FordFulkerson ff(6);
    ff.add_uni_edge(0, 1, 3);
    ff.add_uni_edge(0, 2, 2);
    ff.add_uni_edge(1, 3, 2);
    ff.add_uni_edge(1, 4, 1);
    ff.add_uni_edge(2, 4, 2);
    ff.add_uni_edge(3, 5, 10);
    ff.add_uni_edge(4, 5, 10);
    REQUIRE(ff.max_flow(0, 5) == 5);
}
