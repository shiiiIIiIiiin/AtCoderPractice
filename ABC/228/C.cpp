#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,K;cin>>N>>K;
  vector<vector<int>> P(N,vector<int>(3));
  for(int i=0;i<N;i++)for(int j=0;j<3;j++)cin>>P[i][j];
  
  vector<pair<int,int>> cnt(N);
  
  for(int i=0;i<N;i++)cnt[i].first=0,cnt[i].second=i;
  
  for(int i=0;i<N;i++)for(int j=0;j<3;j++)cnt[i].first+=P[i][j];
  
  sort(cnt.begin(),cnt.end());
  
  int ans[N];
  
  for(int i=0;i<N;i++){
    ans[cnt[N-1-i].second]=i;
  }
  
  for(int i=1;i<=N;i++){
    
    if(cnt[N-K].first-cnt[N-1-ans[i-1]].first<=300)cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
  }
}