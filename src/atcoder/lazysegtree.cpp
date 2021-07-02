#include "catch.hpp"
#include "data_structure/bit.h"
#include <atcoder/all>

// 参考:
// https://betrue12.hateblo.jp/entry/2020/09/22/194541
// https://betrue12.hateblo.jp/entry/2020/09/23/005940

// (1) 区間加算・区間最小値取得

// 各要素の型
using S = ll;
// 操作（写像）を表す値の型
using F = ll;
const S INF = 8e18;
// 区間取得をどのような演算で行うかを定義
S op(S a, S b) { return std::min(a, b); }
// 区間取得演算 op の単位元。基本、定数を返す
// 単位元 e とは、全ての a に対して op(a, e) = op(e, a) = a を満たすもの、
// つまり∞
S e() { return INF; }
// 操作f（e.g. 区間内の全要素に整数fを加算）を、
// 各ノードのdataの値 x に対して作用させる関数
S mapping(F f, S x) { return x + f; }
// 既にこれまでの操作を溜めている lazy に対して、さらに新しい操作を追加する関数
// gがこれまでの操作、fが後に追加する操作
// 可換でない場合は順番に注意
F composition(F f, F g) { return f + g; }
// 区間操作演算 mapping における恒等写像を返す関数。基本、定数を返す
// 全ての a に対してmapping(id, a) = a となるもの
// 区間加算操作の場合は、足しても絶対に対象の値を変えないような値、
// つまり0
F id() { return 0; }
TEST_CASE("lazysegtree1", "[atcoder]")
{
    std::vector<S> v = {0, 1, 2, 3, 4};
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(v);

    // data[p]を返す
    REP(i, SIZE(v)) {
        REQUIRE(seg.get(i) == v[i]);
    }
    // 区間最小値 (op(a[l] .. a[r-1]))を返す
    REQUIRE(seg.prod(0, 5) == 0);
    REQUIRE(seg.prod(2, 4) == 2);
    // 全区間の最小値を返す
    REQUIRE(seg.all_prod() == 0);

    // data[p]にxをセット
    // v = {10, 1, 2, 3, 4}
    seg.set(0, 10);
    // 値が変わったことを確認
    REQUIRE(seg.all_prod() == 1);

    // data[2]に操作(7を加算)
    // v = {10, 1, 9, 3, 4}
    seg.apply(2, 7);
    // 値が変わったことを確認
    REQUIRE(seg.prod(2, 3) == 9);

    // data[1, 2, 3]に操作(10を加算)
    // v = {10, 11, 19, 13, 4}
    seg.apply(1, 4, 10);
    // 値が変わったことを確認
    REQUIRE(seg.prod(0, 1) == 10);
    REQUIRE(seg.prod(1, 2) == 11);
    REQUIRE(seg.prod(2, 3) == 19);
    REQUIRE(seg.prod(3, 4) == 13);
    REQUIRE(seg.prod(4, 5) == 4);
}

// (2) 区間加算・区間最大値取得

using S2 = ll;
using F2 = ll;

const S2 INF2 = 8e18;

S2 op2(S2 a, S2 b) { return std::max(a, b); }
S2 e2() { return -INF2; }
S2 mapping2(F2 f, S2 x) { return f + x; }
F2 composition2(F2 f, F2 g) { return f + g; }
F2 id2() { return 0; }
TEST_CASE("lazysegtree2", "[atcoder]")
{
    std::vector<S2> v = {0, 1, 2, 3, 4};
    atcoder::lazy_segtree<S2, op2, e2, F2, mapping2, composition2, id2> seg(v);

    // data[p]を返す
    REP(i, SIZE(v))
    {
        REQUIRE(seg.get(i) == v[i]);
    }
    // 区間最小値 (op(a[l] .. a[r-1]))を返す
    REQUIRE(seg.prod(0, 5) == 0);
    REQUIRE(seg.prod(2, 4) == 2);
    // 全区間の最小値を返す
    REQUIRE(seg.all_prod() == 0);

    // data[p]にxをセット
    // v = {10, 1, 2, 3, 4}
    seg.set(0, 10);
    // 値が変わったことを確認
    REQUIRE(seg.all_prod() == 1);

    // data[2]に操作(7を加算)
    // v = {10, 1, 9, 3, 4}
    seg.apply(2, 7);
    // 値が変わったことを確認
    REQUIRE(seg.prod(2, 3) == 9);

    // data[1, 2, 3]に操作(10を加算)
    // v = {10, 11, 19, 13, 4}
    seg.apply(1, 4, 10);
    // 値が変わったことを確認
    REQUIRE(seg.prod(0, 1) == 10);
    REQUIRE(seg.prod(1, 2) == 11);
    REQUIRE(seg.prod(2, 3) == 19);
    REQUIRE(seg.prod(3, 4) == 13);
    REQUIRE(seg.prod(4, 5) == 4);
}

// (3) 区間加算・区間和取得
// dataのほうに区間の幅を持たせる
struct S3
{
    ll value; // 実際の値
    int size;  // 区間の幅
};
using F3 = ll;
S3 op3(S3 a, S3 b) { return {a.value + b.value, a.size + b.size}; }
S3 e3() { return {0, 0}; }
S3 mapping3(F3 f, S3 x) { return {x.value + x.size * f, x.size}; }
F3 composition3(F3 f, F3 g) { return f + g; }
F3 id3() { return 0; }
TEST_CASE("lazysegtree3", "[atcoder]")
{
    int n = 5;
    // {0, 0, 0, 0, 0}
    std::vector<S3> v(n, {0, 1});
    atcoder::lazy_segtree<S3, op3, e3, F3, mapping3, composition3, id3> seg(v);

    // data[1, 2, 3]に操作(10を加算)
    // v = {0, 10, 10, 10, 0}
    seg.apply(1, 4, 10);
    // 全要素に操作(100を加算)
    // v = {100, 110, 110, 110, 100}
    seg.apply(0, 5, 100);

    // 値が変わったことを確認
    S3 tmp = seg.prod(2, 5);
    REQUIRE(tmp.value == 320);
    REQUIRE(tmp.size == 3);
}

// (4) 区間変更・区間最小値取得
using S4 = ll;
using F4 = ll;

const S4 INF4 = 8e18;
const F4 ID4 = 8e18;

S4 op4(S4 a, S4 b){ return std::min(a, b); }
S4 e4(){ return INF; }
S4 mapping4(F4 f, S4 x){ return (f == ID4 ? x : f); }
F4 composition4(F4 f, F4 g){ return (f == ID4 ? g : f); }
F4 id4(){ return ID4; }
TEST_CASE("lazysegtree4", "[atcoder]")
{
    int n = 5;
    // {0, 0, 0, 0, 0}
    std::vector<S4> v(n);
    atcoder::lazy_segtree<S4, op4, e4, F4, mapping4, composition4, id4> seg(v);
  
    // TODO
}

// (5) 区間変更・区間最大値取得
using S5 = ll;
using F5 = ll;

const S5 INF5 = 8e18;
const F5 ID5 = 8e18;
S5 op5(S5 a, S5 b) { return max(a, b); }
S5 e5() { return -INF5; }
S5 mapping5(F5 f, S5 x){ return (f == ID5 ? x : f); }
F5 composition5(F5 f, F5 g){ return (f == ID5 ? g : f); }
F5 id5(){ return ID5; }
TEST_CASE("lazysegtree5", "[atcoder]")
{
    // TODO: 未変更

    int n = 5;
    // {0, 0, 0, 0, 0}
    std::vector<S5> v(n);
    atcoder::lazy_segtree<S5, op5, e5, F5, mapping5, composition5, id5> seg(v);

    // data[1, 2, 3]に操作(10で上書き)
    // v = {0, 10, 10, 10, 0}
    seg.apply(1, 4, 10);
    // data[3, 4, 5]に操作(20で上書き)
    // v = {0, 10, 20, 20, 20}
    seg.apply(3, 5, 20);

    // // 値が変わったことを確認
    // S5 tmp = seg.prod(1, 4);
    // REQUIRE(tmp.value == 50);
    // REQUIRE(tmp.size == 3);
}

// (6) 区間変更・区間和取得
struct S6 {
    ll value;
    int size;
};
using F6 = ll;
const F6 ID6 = 8e18;
S6 op6(S6 a, S6 b){ return {a.value + b.value, a.size + b.size}; }
S6 e6(){ return {0, 0}; }
S6 mapping6(F6 f, S6 x){
    if(f != ID6) x.value = f*x.size;
    return x;
}
F6 composition6(F6 f, F6 g){ return (f == ID6 ? g : f); }
F6 id6(){ return ID6; } // TODO:: return 0??
TEST_CASE("lazysegtree6", "[atcoder]")
{
    int n = 5;
    // {0, 0, 0, 0, 0}
    std::vector<S6> v(n, {0, 1});
    atcoder::lazy_segtree<S6, op6, e6, F6, mapping6, composition6, id6> seg(v);

    // data[1, 2, 3]に操作(10で上書き)
    // v = {0, 10, 10, 10, 0}
    seg.apply(1, 5, 10);
    // data[3, 4, 5]に操作(20で上書き)
    // v = {0, 10, 20, 20, 20}
    seg.apply(3, 5, 20);

    // 値が変わったことを確認
    S6 tmp = seg.prod(1, 4);
    REQUIRE(tmp.value == 50);
    REQUIRE(tmp.size == 3);
}
