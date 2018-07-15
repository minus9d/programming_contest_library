// ただ一つだけ閉路があるとき、その閉路に属する頂点の集合を探して返す
// もっとよい書き方がありそう…
// verify: https://codejam.withgoogle.com/codejam/contest/4384486/dashboard#s=p2
#pragma once
#include "common.h"

void dfs(int v, int from, set<int>& seen, const vector<vector<int>>& edges, vector<int>& backtrace, int& v1, int &v2) {
    for (auto nei: edges[v]) {
        if (nei == from) continue;
        if (seen.count(nei)) {
            v1 = v;
            v2 = nei;
            break;
        }
        else {
            backtrace[nei] = v;
            seen.insert(nei);
            dfs(nei, v, seen, edges, backtrace, v1, v2);
        }
    }
}

set<int> find_loop(int N, const vector<vector<int>>& edges) {
    set<int> seen;
    vector<int> backtrace(N);
    backtrace[0] = -1;
    seen.insert(0);
    int v1 = -1, v2 = -1;
    dfs(0, -1, seen, edges, backtrace, v1, v2);

    set<int> loop;
    loop.insert(v1);
    int v = v2;
    while(!loop.count(v)) {
        loop.insert(v);
        v = backtrace[v];
    }

    //cerr << "loop: ";
    //for(auto v: loop) cerr << v << " ";
    //cerr << endl;

    vector<int> ans(N);
    set<int> used;
    set<int> vs;
    for (auto v : loop) {
        ans[v] = 0;
        used.insert(v);
        vs.insert(v);
    }

    int dist = 1;
    while (!vs.empty()) {
        set<int> next_vs;
        for (auto v : vs) {
            for (auto nei : edges[v]) {
                if (!used.count(nei)) {
                    next_vs.insert(nei);
                    used.insert(nei);
                    ans[nei] = dist;
                }
            }
        }
        vs = next_vs;
        ++dist;
    }

    REP(v, N) {
        cout << " " << ans[v];
    }

    return loop;
}