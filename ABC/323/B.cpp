#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<string> S(N);
  for(int i=0;i<N;i++)cin>>S[i];
  int cnt[N];
  for(int i=0;i<N;i++)cnt[i]=0;
  
  for(int i=0;i<N;i++){
    for(int j=0;j<S[i].size();j++)if(S[i][j]=='o')cnt[i]++;
  }
  
  //for(int i=0;i<N;i++)cout<<cnt[i]<<" ";
  
  
  for(int i=N;i>=0;i--){
    for(int j=0;j<N;j++){
      if(cnt[j]==i)cout<<j+1<<" ";
    }
  }
  
}