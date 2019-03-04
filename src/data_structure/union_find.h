#pragma once
#include "common.h"
// Union-Find木
// クラスとして実装
// 参考：プログラミングコンテストチャレンジブック 第一版 p84

class UnionFind
{
public:
    UnionFind(){};
    ~UnionFind(){};
    void init(int num_entries) {
        num_entries_ = num_entries;
        par_.resize(num_entries_);
        rank_.resize(num_entries_, 0);
        member_num_.resize(num_entries_, 1);
        REP(i, num_entries_) {
            par_[i] = i;
        }
    }
    int find(int x) {
        if (par_[x] == x) return x;
        else return par_[x] = find(par_[x]);
    }
    void unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return;
        if (rank_[x] < rank_[y]) {
            par_[x] = y;
            member_num_[y] += member_num_[x];
            member_num_[x] = 0;
        } else {
            par_[y] = x;
            member_num_[x] += member_num_[y];
            member_num_[y] = 0;
            if (rank_[x] == rank_[y]) rank_[x]++;
        }
    }
    bool same(int x, int y) { return find(x) == find(y); }
    int size(int x) {
        return member_num_[this->find(x)];
    }
private:
    int num_entries_;
    std::vector<int> par_;
    std::vector<int> rank_;
    std::vector<int> member_num_;
};
