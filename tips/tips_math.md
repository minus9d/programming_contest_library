## XOR

* Nを偶数とすると、N ^ (N + 1)は必ず1になる
  * 問題: [ABC121 D \- XOR World](https://atcoder.jp/contests/abc121/tasks/abc121_d)
* a^b=b^a
* a^(b^c)=(a^b)^c
* a^a=0

* 以下は未確認  https://twitter.com/shun_skycrew/status/1274711385335664646
    * a+b=a^b + 2(a&b)
    * (4a)^(4a+1)^(4a+2)^(4a+3)=0


## 中央値

### ヒント

* 中央値の言い換えを覚える
  * 中央値を数列の真ん中とする。真ん中が2つあるときは数値の大きい方とする
  * 長さMの数列が与えられたとき、「X以上の要素数がceil(M/2)個以上ある」最大のXが中央値
* 上記言い換えにより二分探索が使えるようになる
  * 数列の要素がX以上なら+1, X未満なら-1などとできる
  * 例: [Median of Medians](https://atcoder.jp/contests/arc101/tasks/arc101_b)
