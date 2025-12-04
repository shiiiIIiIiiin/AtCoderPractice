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
    
    ll N,M;cin>>N>>M;
    //k桁の数字であってMで割ったあまりがｒのものがいくつあるかだけわかればOK

    vector<vector<ll>> cnt(11,vector<ll>());
    vector<ll> A(N);
    for(int i=0;i<N;i++)cin>>A[i];
    sort(A.begin(),A.end());

    for(int i=0;i<N;i++){
        cnt[to_string(A[i]).size()].push_back(A[i]);
    }

    ll ans=0;

    for(ll i=1;i<11;i++)for(ll j=1;j<11;j++){
        map<ll,ll> mpi,mpj;

        for(int k=0;k<cnt[i].size();k++)mpi[(cnt[i][k]*modpow(10LL,j,M))%M]++;
        for(int k=0;k<cnt[j].size();k++)mpj[cnt[j][k]%M]++;

        for(auto [r,c]:mpi){
            ans+=c*mpj[(M-r)%M];
        }
    }

    cout<<ans<<endl;
}