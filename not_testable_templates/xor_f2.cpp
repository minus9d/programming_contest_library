// F_2におけるベクトルの基底を求める  xorに使える
// verify: https://atcoder.jp/contests/agc045/tasks/agc045_a

int solve(vector<ll> As) {

    // ベクトル基底の持ち方
    // 以下の2つのどちらでも良い
    set<ll, greater<ll>> bases;
    // vector<ll> bases;

    for(auto a: As) {
        ll a = As[i];
        for (auto b: bases) chmin(a, a ^ b);
            // これまでの基底で表せないベクトルなら基底に追加
            if (a) {
                bases.insert(a);
                // bases.pb(a);
            }
        }
    }
}

