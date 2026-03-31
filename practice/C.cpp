#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

using ll=long long;

int main(){
    int T;cin>>T;

    for(;T--;){
        ll N,M,A,B;cin>>N>>M>>A>>B;
        cout<<floor_sum(N,M,A,B)<<endl;
    }
}