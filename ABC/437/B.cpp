#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll=long long;

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

    int H,W,N;cin>>H>>W>>N;
    vector<int> B(N);
    vector<set<int>> st(H);

    for(int i=0;i<H;i++)for(int j=0;j<W;j++){
        int a;cin>>a;
        st[i].insert(a);
    }

    for(int i=0;i<N;i++)cin>>B[i];

    int ans=-1;

    for(int i=0;i<H;i++){
        int cnt=0;
        for(int j=0;j<N;j++)if(st[i].count(B[j]))cnt++;
        ans=max(ans, cnt);
    }
    cout<<ans<<endl;
}