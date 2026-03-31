#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

int main() {
    int N,Q;cin>>N>>Q;
    dsu uf(N+1);

    for(;Q--;){
        int t,u,v;cin>>t>>u>>v;
        if(t==0){
            uf.merge(u,v);
        }
        else{
            cout<<(uf.same(u,v) ? 1:0)<<endl;
        }
    }
}