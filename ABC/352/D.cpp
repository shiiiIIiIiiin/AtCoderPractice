#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
  int N,K;cin>>N>>K;
  vector<int> P(N);
  for(int i=0;i<N;i++)cin>>P[i];
  vector<int> id(N+1);
  for(int i=0;i<N;i++)id[P[i]]=i;//iはP[id[i]]に入ってる
  
  int ans=INT_MAX;
  set<int> s;
  for(int i=1;i<=K;i++)s.insert(id[i]);
  
  ans=min(ans,*--s.end()-*s.begin());
    
  
  for(int a=1;a+K<=N;a++){
    s.erase(id[a]);
    s.insert(id[a+K]);
    ans=min(ans,*--s.end()-*s.begin());
   
  }
  
  cout<<ans<<endl;
}