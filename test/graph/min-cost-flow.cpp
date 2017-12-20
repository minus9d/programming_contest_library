#include "catch.hpp"
#include "graph/min-cost-flow.h"

TEST_CASE("min-cost-flow-potential", "[graph]") {
    MinCostFlowPotential mcfp;
    mcfp.init(5);
    
    // p199の絵に従う
    // from, to, cap, costの順
    mcfp.add_edge(0, 1, 10, 2);
    mcfp.add_edge(0, 2, 2, 4);
    mcfp.add_edge(1, 2, 6, 6);
    mcfp.add_edge(1, 3, 6, 2);
    mcfp.add_edge(2, 4, 5, 2);
    mcfp.add_edge(3, 2, 3, 3);
    mcfp.add_edge(3, 4, 8, 6);

    REQUIRE(mcfp.min_cost_flow(0, 4, 9) == 80);
}

TEST_CASE("min-cost-flow-bellman-ford", "[graph]") {
    MinCostFlowBellmanFord mcf;
    mcf.init(5);
    
    // p199の絵に従う
    // from, to, cap, costの順
    mcf.add_edge(0, 1, 10, 2);
    mcf.add_edge(0, 2, 2, 4);
    mcf.add_edge(1, 2, 6, 6);
    mcf.add_edge(1, 3, 6, 2);
    mcf.add_edge(2, 4, 5, 2);
    mcf.add_edge(3, 2, 3, 3);
    mcf.add_edge(3, 4, 8, 6);

    REQUIRE(mcf.min_cost_flow(0, 4, 9) == 80);
}

