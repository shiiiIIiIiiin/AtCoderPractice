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

vector<int> ans;

void dfs(vector<int> &nex,vector<vector<pair<ll,int>>> &G){
    map<ll,vector<int>> mp;

    for(auto pos:nex){
        for(auto v:G[pos]){
            mp[v.first].push_back(v.second);
        }
    }

    for(auto p:mp){
        sort(p.second.begin(), p.second.end());
        for(auto v:p.second)ans.push_back(v);
        dfs(p.second,G);
    }
    
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    
    int N;cin>>N;
    vector<vector<pair<ll,int>>> G(N+1);

    for(int i=1;i<=N;i++){
        ll x,y;cin>>x>>y;
        G[x].push_back({y,i});
    }

    for(int i=1;i<=N;i++)sort(G[i].begin(), G[i].end());

    vector<int> nex={0};
    
    dfs(nex,G);

    for(int i=0;i<ans.size();i++)cout<<ans[i]<<" ";
    cout<<endl;
}