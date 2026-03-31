#include<bits/stdc++.h>
using namespace std;

long long a=0,b=0;

void dfs(int pos,int N,long long &ans,vector<int> &K){
  
  if(pos==N){
    ans=min(ans,max(a,b));
    return;
  }
  
  a+=K[pos];
  dfs(pos+1,N,ans,K);
  a-=K[pos];
  
  b+=K[pos];
  dfs(pos+1,N,ans,K);
  b-=K[pos];
  
  return;
}

int main(){
  int N;cin>>N;
  vector<int> K(N);
  for(int i=0;i<N;i++)cin>>K[i];
  
  long long ans=LLONG_MAX;
  
  dfs(0,N,ans,K);
  
  cout<<ans<<endl;
}