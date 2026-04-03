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

ll N, K, P;

void fill_cnt(vector<vector<ll>>& cnt, vector<ll>& A) {

    int n = A.size();

    for (int s = 0; s < (1 << n); s++) {
        ll sum = 0, c = 0;
        for (int i = 0; i < n; i++) {
            if ((s >> i) & 1) {
                sum += A[i];
                c++;
            }
        }

        cnt[c].push_back(sum);
    }

}

int main() {
    cin >> N >> K >> P;
    vector<ll> A1, A2;
    for (int i = 0; i < N; i++) {
        ll a; cin >> a;
        if (i % 2 == 0)A1.push_back(a);
        else A2.push_back(a);
    }

    vector<vector<ll>> cnt1(21, vector<ll>()), cnt2(21, vector<ll>());

    fill_cnt(cnt1, A1);
    fill_cnt(cnt2, A2);

    for (int i = 0; i < 21; i++)sort(cnt2[i].begin(), cnt2[i].end());

    ll ans = 0;

    for (int i = 0; i < 21; i++) {
        int target = K - i;// cnt2[target] を調べる
        if (target < 0)break;
        if (target >= cnt2.size())continue;

        for (auto v : cnt1[i]) {
            ll l = -1, r = cnt2[target].size(), m;

            while (r - l > 1) {
                m = (r + l) / 2;
                if (cnt2[target][m] + v <= P)l = m;
                else r = m;
            }

            ans += r;
        }

        
    }

    cout<<ans<<endl;


}