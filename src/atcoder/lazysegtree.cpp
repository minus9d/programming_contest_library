#include "catch.hpp"
#include "data_structure/bit.h"
#include <atcoder/all>

// 「整数の数列に対する、区間加算操作と区間最小値取得」の機能を持つセグメント木

// 各要素の型
using S = int;
// 操作（写像）を表す値の型
using F = int;
// 区間取得をどのような演算で行うかを定義
S op(S a, S b) { return std::min(a, b); }
// 操作f（e.g. 区間内の全要素に整数fを加算）を、
// 各ノードのdataの値 x に対して作用させる関数
S mapping(F f, S x) { return x + f; }
// 既にこれまでの操作を溜めている lazy に対して、さらに新しい操作を追加する関数
// gがこれまでの操作、fが後に追加する操作
// 可換でない場合は順番に注意
F composition(F f, F g) { return f + g; }

// 区間取得演算 op の単位元。基本、定数を返す
// 単位元 e とは、全ての a に対して op(a, e) = op(e, a) = a を満たすもの、
// つまり∞
S e() { return int(1e9) + 1; }
// 区間操作演算 mapping における恒等写像を返す関数。基本、定数を返す
// 全ての a に対してmapping(id, a) = a となるもの
// 区間加算操作の場合は、足しても絶対に対象の値を変えないような値、
// つまり0
F id() { return 0; }

// 「整数の数列に対する、区間加算操作と区間最小値取得」の機能を持つセグメント木
// cf. https://betrue12.hateblo.jp/entry/2020/09/22/194541
TEST_CASE("lazysegtree1", "[atcoder]")
{
    std::vector<int> v = {0, 1, 2, 3, 4};
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

// 「整数の数列に対する、区間加算操作と区間和取得」の機能を持つセグメント木
// dataのほうに区間の幅を持たせる
// cf. https://betrue12.hateblo.jp/entry/2020/09/22/194541
// 各要素の型
struct S2
{
    int value; // 実際の値
    int size;  // 区間の幅
};
// 操作（写像）を表す値の型
using F2 = int;
// 区間取得をどのような演算で行うかを定義
S2 op2(S2 a, S2 b) { return {a.value + b.value, a.size + b.size}; }
// 区間取得演算 op の単位元。基本、定数を返す
// 単位元 e とは、全ての a に対して op(a, e) = op(e, a) = a を満たすもの、
// つまり∞
S2 e2() { return {0, 0}; }
// 操作f（e.g. 区間内の全要素に整数fを加算）を、
// 各ノードのdataの値 x に対して作用させる関数
S2 mapping2(F2 f, S2 x) { return {x.value + x.size * f, x.size}; }
// 既にこれまでの操作を溜めている lazy に対して、さらに新しい操作を追加する関数
// gがこれまでの操作、fが後に追加する操作
// 可換でない場合は順番に注意
F2 composition2(F2 f, F2 g) { return f + g; }
// 区間操作演算 mapping における恒等写像を返す関数。基本、定数を返す
// 全ての a に対してmapping(id, a) = a となるもの
// 区間加算操作の場合は、足しても絶対に対象の値を変えないような値、
// つまり0
F2 id2() { return 0; }
TEST_CASE("lazysegtree2", "[atcoder]")
{
    int n = 5;
    // {0, 0, 0, 0, 0}
    std::vector<S2> v(n, {0, 1});
    atcoder::lazy_segtree<S2, op2, e2, F2, mapping2, composition2, id2> seg(v);

    // data[1, 2, 3]に操作(10を加算)
    // v = {0, 10, 10, 10, 0}
    seg.apply(1, 4, 10);
    // 全要素に操作(100を加算)
    // v = {100, 110, 110, 110, 100}
    seg.apply(0, 5, 100);

    // 値が変わったことを確認
    S2 tmp = seg.prod(2, 5);
    REQUIRE(tmp.value == 320);
    REQUIRE(tmp.size == 3);
}

// 「区間中の値を全てある値 x に更新する」という区間更新操作と、区間和取得の機能を持たせる
// cf. https://betrue12.hateblo.jp/entry/2020/09/22/194541
// 各要素の型
struct S3
{
    int value; // 実際の値
    int size;  // 区間の幅
};
using F3 = int;
// 擬似的に恒等写像として扱う値
const F3 ID = int(2e9); 
S3 op3(S3 a, S3 b) { return {a.value + b.value, a.size + b.size}; }
S3 e3() { return {0, 0}; }
// 操作f（e.g. 区間内の全要素に整数fを加算）を、
// 各ノードのdataの値 x に対して作用させる関数
// f が ID ならばそのまま x を返す。
// そうでなければ区間内の値全てを f に変更するので、x.value = x.size * f とする。
S3 mapping3(F3 f, S3 x) {
    if (f != ID)
        x.value = x.size * f;
    return x;
}
// 既にこれまでの操作を溜めている lazy に対して、さらに新しい操作を追加する関数
// gがこれまでの操作、fが後に追加する操作
// 可換でない場合は順番に注意
// fがIDならそのままgを返す。そうでなければfを返す
F3 composition3(F3 f, F3 g) { return (f == ID ? g : f); }
// 区間操作演算 mapping における恒等写像を返す関数。基本、定数を返す
// 全ての a に対してmapping(id, a) = a となるもの
// 区間加算操作の場合は、足しても絶対に対象の値を変えないような値、
// つまり0
F3 id3() { return 0; }
TEST_CASE("lazysegtree3", "[atcoder]")
{
    int n = 5;
    // {0, 0, 0, 0, 0}
    std::vector<S2> v(n, {0, 1});
    atcoder::lazy_segtree<S2, op2, e2, F2, mapping2, composition2, id2> seg(v);

    // data[1, 2, 3]に操作(10で上書き)
    // v = {0, 10, 10, 10, 0}
    seg.apply(1, 4, 10);
    // data[3, 4, 5]に操作(20で上書き)
    // v = {0, 10, 20, 20, 20}
    seg.apply(3, 5, 20);

    // 値が変わったことを確認
    S2 tmp = seg.prod(1, 4);
    REQUIRE(tmp.value == 50);
    REQUIRE(tmp.size == 3);
}