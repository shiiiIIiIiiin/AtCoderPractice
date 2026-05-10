//#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll = long long;

const ll MOD = 998244353;
const ll MOD2 = 1'000'000'007;

long long modinv(long long a, long long m) {
    long long b = m, u = 1, v = 0;
    while (b) {
        long long t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= m; if (u < 0) u += m;
    return u;
}

long long modpow(long long a, long long n, long long mod) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

ll dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };
const ll INF = LLONG_MAX / 2;


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    //L=SのものとR=Tのものだけ見ればいい
    int N, M; cin >> N >> M;
    vector<vector<ll>> memol(N + 1), memor(N + 1);
    set<pair<ll, ll>> st;
    vector<ll> min_l(N + 1, INF), max_r(N + 1, -1);
    map<pair<ll, ll>, ll> mp;

    for (int i = 0; i < M; i++) {
        ll l, r; cin >> l >> r;
        memol[l].push_back(r);
        memor[r].push_back(l);
        st.insert({ l,r });
        min_l[l] = min(min_l[l], r);
        max_r[r] = max(max_r[r], l);
        mp[{l, r}]++;
    }

    for (int i = N - 1; i >= 1; i--) min_l[i] = min(min_l[i + 1], min_l[i]);
    for (int i = 1; i <= N; i++) max_r[i] = max(max_r[i - 1], max_r[i]);

    for (int i = 0; i <= N; i++) {
        sort(memol[i].begin(), memol[i].end());
        sort(memor[i].begin(), memor[i].end());
    }

    int Q; cin >> Q;

    for (; Q--;) {
        int s, t; cin >> s >> t;

        if (st.count({ s,t })) {
            if (mp[{s, t}] >= 2) {
                cout << "Yes" << endl;
                continue;
            }
            if (min_l[s] < t || s < max_r[t]) {
                cout << "Yes" << endl;
                continue;
            }
        }

        //memol[s]のうちｔ以下で一番大きいもの
        //memor[t]のうちs以上で一番小さいもの

        if (memol[s].size() == 0 || memor[t].size() == 0) {
            cout << "No" << endl;
            continue;
        }

        auto it = lower_bound(memol[s].begin(), memol[s].end(), t);
        auto itr = upper_bound(memor[t].begin(), memor[t].end(), s);

        if (it == memol[s].begin()) {
            cout << "No" << endl;
            continue;
        }

        auto itl = prev(it);

        if (itr == memor[t].end()) {
            cout << "No" << endl;
            continue;
        }

        int l = *itr, r = *itl;

        if (l <= r + 1)cout << "Yes" << endl;
        else cout << "No" << endl;
    }

}