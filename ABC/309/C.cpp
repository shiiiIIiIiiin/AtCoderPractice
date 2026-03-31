#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
    ll N,K;cin>>N>>K;
    vector<pair<ll,ll>> A(N);
    ll cnt=0;
    for(int i=0;i<N;i++){
        cin>>A[i].first>>A[i].second;
        cnt+=A[i].second;
    }
    
    sort(A.begin(),A.end());

    if(cnt<=K){
        cout<<1<<endl;
        return 0;
    }

    for(int i=0;i<N;i++){
        cnt-=A[i].second;
        if(cnt<=K){
            cout<<A[i].first+1<<endl;
            return 0;
        }
    }
    
}