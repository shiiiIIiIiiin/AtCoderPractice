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


ll f(ll x,vector<ll> &A){
    ll l=-1,r=A.size(),m;

    while(r-l>1){
        m=(l+r)/2;
        if(A[m]<=x)l=m;
        else r=m;
    }

    return r;
}

ll f2(ll x,vector<ll> &A){
    ll l=-1,r=A.size(),m;

    while(r-l>1){
        m=(l+r)/2;
        if(A[m]<x)l=m;
        else r=m;
    }

    return r;
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    
    ll N,M;cin>>N>>M;
    vector<ll> A(N),B(M);
    for(int i=0;i<N;i++)cin>>A[i];
    for(int i=0;i<M;i++)cin>>B[i];
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    vector<ll> cnt(N),cnt2(M);
    ll ans=0;

    for(int i=0;i<N;i++)cnt[i]=f(A[i],B);
    for(int i=0;i<M;i++)cnt2[i]=f2(B[i],A);

    for(int i=0;i<N;i++){
        ans+=(2*cnt[i]-M+MOD)*A[i];
        ans%=MOD;
    }
    for(int i=0;i<M;i++){
        ans+=(2*cnt2[i]-N+MOD)*B[i];
        ans%=MOD;
    }

    cout<<ans<<endl;
}