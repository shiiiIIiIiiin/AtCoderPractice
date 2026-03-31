//#define _GLIBCXX_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <unordered_map>
#include <stack>
#include <string>
#include <cmath>
#include <iomanip>
#include <deque>
#include <unordered_set>
#include <locale>
#include <random>

using namespace std;
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


int dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };

const ll INF = LLONG_MAX / 2;

//cin.tie(nullptr);
//ios::sync_with_stdio(false);

int main() {
    ll M, A, B; cin >> M >> A >> B;

    //(x,y)を全探索したい、(sn-1,sn-2)をMで割ったあまりは全部でM^2通りぐらいある
    //一回探索した(sn-1%M,sn-2%M)はもう二度と探索しなくても答えが分かってる

    map<pair<int, int>, pair<int, int>> mp;

    for (int x = 0; x < M; x++)for (int y = 0; y < M; y++) {
        mp[{x, y}] = { y,(A * y + B * x) % M };
    }

    //mpをグラフと見たときに、0を含むもの以外はOK
    unordered_set<int> st;
    unordered_set<int> ng;

    ll ans = 0;

    for (int x = 0; x < M; x++)ng.insert(x * M);
    for (int y = 0; y < M; y++)ng.insert(y);


    int cnt = 0;

    for (int x = 1; x < M; x++)for (int y = 1; y < M; y++) {
        if (st.count(x * M + y))continue;
        st.insert(x * M + y);
        unordered_set<int> kouho;
        pair<int, int> pos = { x,y };
        bool f = true;//0を含まないか
        kouho.insert(pos.first * M + pos.second);
        
        while (true) {
            auto nex = mp[pos];
            
            if (nex.first == 0 || nex.second == 0 || ng.count(nex.first * M + nex.second)) {
                kouho.insert(nex.first * M + nex.second);
                for (auto v : kouho)ng.insert(v);
                f = false;
                break;
            }

            if (st.count(nex.first * M + nex.second))break;

            st.insert(nex.first * M + nex.second);
            kouho.insert(nex.first * M + nex.second);
            pos = nex;
        }

        if (f) {
            ans += kouho.size();
            cnt++;
        }
    }

    //cout << "debug:" << cnt << endl;

    cout << ans << endl;
}