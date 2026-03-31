#include<bits/stdc++.h>
using namespace std;

long long kukancount(long long I,long long k,vector<long long> &C){
  long long l=I,r=C.size(),m;
  
  while(r-l>1){
    m=(l+r)/2;
    if(k>=C[m])l=m;
    else r=m;
  }
  
  //cout<<l-I<<endl;
  
  return l-I;
  
}

int main(){
  int N;cin>>N;
  vector<pair<long long,long long>> range(N);
  for(int i=0;i<N;i++)cin>>range[i].first>>range[i].second;
  sort(range.begin(),range.end());
  vector<long long> C(N);
  for(int i=0;i<N;i++)C[i]=range[i].first;
  
  long long ans=0;
  
  for(int i=0;i<N;i++){
    ans+=kukancount(i,range[i].second,C);
  }
  
  cout<<ans<<endl;
}