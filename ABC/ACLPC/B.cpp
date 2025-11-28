#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

using ll=long long;

int main() {
    int N,Q;cin>>N>>Q;
    fenwick_tree<ll> bit(N);

    for(int i=0;i<N;i++){
        ll a;cin>>a;
        bit.add(i,a);
    }

    for(;Q--;){
        int t;cin>>t;
        if(t==0){
            ll p,x;cin>>p>>x;
            bit.add(p,x);
        }
        else{
            ll l,r;cin>>l>>r;

            cout<<bit.sum(l,r)<<endl;
        }
    }
}