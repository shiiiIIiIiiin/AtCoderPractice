#include <bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  string T;cin>>T;
  vector<string> S(N);
  for(int i=0;i<N;i++)cin>>S[i];
  
  vector<int> cnt(N,0),cnt2(N,0);
  
  for(int i=0;i<N;i++){//cntの決定
    
    int id=0;
    for(int j=0;j<S[i].size();j++){
      if(S[i][j]==T[id]){
        cnt[i]++;
        id++;
        if(id==T.size())break;
      }
    }
    
  }
  
  for(int i=0;i<N;i++){//cnt2の決定
    
    int id=T.size()-1;
    for(int j=S[i].size()-1;j>=0;j--){
      if(S[i][j]==T[id]){
        cnt2[i]++;
        id--;
        if(id==-1)break;
      }
    }
    
  }
  
  //cnt[i]+cnt2[j]>=T.size()となる(i,j)の数を数える
  
  sort(cnt2.begin(),cnt2.end());
  long long ans=0;
  
  for(int i=0;i<N;i++){
    int a=cnt[i];
    
    int l=-1,r=N,m;
    while(r-l>1){
      m=(r+l)/2;
      
      if(a+cnt2[m]<T.size())l=m;
      else r=m;
    }
    
    ans+=N-1-r+1;
  }
  
  cout<<ans<<endl;
  
}