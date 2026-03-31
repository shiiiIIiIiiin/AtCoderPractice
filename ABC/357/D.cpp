#include<bits/stdc++.h>
using namespace std;

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

int main(){
  ll N;cin>>N;
  string S=to_string(N);
  ll s=S.size();
  
  ll ans=N,cnt=modpow(10LL,(s*(N%(MOD-1)))%(MOD-1),MOD)-1;
  
  cnt%=MOD;
  cnt*=modinv(modpow(10LL,s,MOD)-1,MOD);
  cnt%=MOD;
  
  cout<<((N%MOD)*cnt)%MOD<<endl;
}