#include "catch.hpp"
#include "graph/bipartite-matching.h"

TEST_CASE("bipartite-matching", "[graph]") {
    // コンピュータの数
    const int N = 4;
    // 人の数
    const int K = 6;

    BipartiteMatching bm(N, K);

    bm.add_edge(0, 0);
    bm.add_edge(0, 1);
    bm.add_edge(0, 2);
    bm.add_edge(1, 3);
    bm.add_edge(2, 1);
    bm.add_edge(3, 4);

    int max_pair = bm.bipartite_matching();
    REQUIRE(max_pair == 4);
}

TEST_CASE("bipartite-matching-ff", "[graph]") {
    const int N = 4;
    const int K = 6;
    BipartiteMatchingFF bm(N, K);

    bm.add_edge(0, 0);
    bm.add_edge(0, 1);
    bm.add_edge(0, 2);
    bm.add_edge(1, 3);
    bm.add_edge(2, 1);
    bm.add_edge(3, 4);

    int max_pair = bm.bipartite_matching();
    REQUIRE(max_pair == 4);
}


TEST_CASE("bipartite-matching-compare", "[graph]") {
    REP(i, 100) {
        const int N = 100 + rand() % 10;
        const int K = 100 + rand() % 10;
        BipartiteMatching bm1(N, K);
        BipartiteMatchingFF bm2(N, K);

        set<pair<int,int>> edges;
        REP(n, N) {
            REP(k, K) {
                if (rand() % 2) {
                    bm1.add_edge(n, k);
                    bm2.add_edge(n, k);
                    edges.insert(mp(n, k));
                }
            }
        }

        int max_pair1 = bm1.bipartite_matching();
        int max_pair2 = bm2.bipartite_matching();
        if (max_pair1 != max_pair2) {
            cout << "error! " << endl;
            for(auto e: edges) cout << "  " << e.first << " " << e.second << endl;
        }
        CHECK(max_pair1 == max_pair2);
    }
}
