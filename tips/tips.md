## 数え上げ

### ヒント

* 配列の長さが40程度であれば、半分全列挙を疑う (meet in the middle)
  * 2^40の全列挙は無理だが2^20の全列挙は可能

### 実例

* [C: String Coloring \- AtCoder Grand Contest 026 \| AtCoder](https://agc026.contest.atcoder.jp/tasks/agc026_c)
  * 問題
    * 



## 部分配列

配列の中から条件を満たす最高の配列を見つける系の問題。

### ヒント

* 配列の長さが10^5であれば、以下ができないか考える
  * 部分配列の左端を固定したとき、部分配列の右端をlog n以下で決定することができないか？
  * しゃくとり法は適用できないか？

### 実例

* [Dashboard \- Kickstart Round D 2018 \- Google Code Jam](https://code.google.com/codejam/contest/6364486/dashboard#s=p0&a=2)
  * 問題
    * 奇数の要素数がO以下、かつ、要素の合計数がD以下、という条件で、要素の合計数が最大となる部分配列を見つける
    * 配列の長さ10^5
  * 解法
    * しゃくとり法 (two-pointers)を使う


## 桁DP

### ヒント 

### 実例

* https://kotamanegi.com/Problems/view/?page=72
  * 問題
    * 桁和がNとなる数の中でK番目に小さい数を求める
  * 解法
    * 先頭に0が並ぶことを許容すれば、「桁数がdで桁和がNになる数の総数」を求めるのはDPで容易にできる。
    * あとは "1", "2", ..., "9", "1X", "2X", ..., "9X", "1XX", "2XX", ..., "9XX"と先頭の数字を固定しながらXXが取りうる数をカウントし、Kから引いていく
  