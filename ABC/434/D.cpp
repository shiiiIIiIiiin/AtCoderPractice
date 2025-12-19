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

    int N;cin>>N;
    vector<vector<ll>> imos(2010,vector<ll>(2010,0));
    vector<ll> U(N),D(N),L(N),R(N);

    for(int i=0;i<N;i++){
        ll u,d,l,r;cin>>u>>d>>l>>r;
        U[i]=u,D[i]=d,L[i]=l,R[i]=r;
        imos[u][l]++;
        imos[d+1][l]--;
        imos[u][r+1]--;
        imos[d+1][l+1]++;
    }
    
    for(int j=0;j<2010;j++)for(int i=1;i<2010;i++)imos[i][j]+=imos[i-1][j];
    for(int i=0;i<2010;i++)for(int j=1;j<2010;j++)imos[i][j]+=imos[i][j-1];

    ll ans_base=0;
    vector<vector<ll>> imos2(2010,vector<ll>(2010,0));
    for(int i=0;i<2010;i++)for(int j=0;j<2010;j++){
        if(imos[i][j]==1)imos2[i][j]++;
        else ans_base++;
    }

    for(int j=0;j<2010;j++)for(int i=1;i<2010;i++)imos2[i][j]+=imos2[i-1][j];
    for(int i=0;i<2010;i++)for(int j=1;j<2010;j++)imos2[i][j]+=imos2[i][j-1];

    for(int i=0;i<N;i++){
        ll u=U[i],d=D[i],l=L[i],r=R[i];
        ll cnt=imos2[d][r]-imos2[u-1][r]+imos2[u-1][l-1]-imos[d][l-1];
        cout<<ans_base+cnt<<endl;
    }
}