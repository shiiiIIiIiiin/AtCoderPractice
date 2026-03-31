#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
    int N;cin>>N;
    vector<int> P(N+1),Q(N+1),Qinv(N+1);
    for(int i=1;i<=N;i++)cin>>P[i];
    for(int i=1;i<=N;i++){
        cin>>Q[i];
        Qinv[Q[i]]=i;
    }
    
    for(int i=1;i<=N;i++)cout<<Q[P[Qinv[i]]]<<" ";
}