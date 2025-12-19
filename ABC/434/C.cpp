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

    int T;cin>>T;

    for(;T--;){
        ll N,H;cin>>N>>H;
        
        ll pl=H,pr=H;//pl以上pr以下に存在することが可能
        vector<ll> t(N+1,0),l(N+1,0),u(N+1,0);
        for(int i=0;i<N;i++)cin>>t[i+1]>>l[i+1]>>u[i+1];

        bool can=true;

        for(int i=1;i<=N;i++){
            ll time=t[i]-t[i-1];

            if((pr<l[i]||u[i]<pl)&&min(labs(pr-l[i]),labs(pl-u[i]))>time){
                can=false;
                break;
            }

            pl-=time;
            pr+=time;

            pl=max(l[i],pl);
            pr=min(u[i],pr);
        }

        cout<<(can ? "Yes":"No")<<endl;

    }
    
}