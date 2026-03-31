#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
  ll N,D,P;cin>>N>>D>>P;
  vector<ll> F(N);
  for(int i=0;i<N;i++)cin>>F[i];
  
  sort(F.begin(),F.end());
  int cnt=N-1;
  long long ans=0;
  
  while(true){
    ll sf=0;
    for(int i=0;i<D;i++){
      sf+=F[cnt];
      cnt--;
      if(cnt==-1)break;
    }
    
    if(sf>=P)ans+=P;
    else ans+=sf;
    
    if(cnt==-1)break;
  }
  
  
  cout<<ans<<endl;
}