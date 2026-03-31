#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,W;cin>>N>>W;
  vector<pair<long long,long long>> T(N);
  for(int i=0;i<N;i++)cin>>T[i].first>>T[i].second;
  
  sort(T.begin(),T.end());
  int cnt=N-1;
  long long ans=0;
  while(W>0&&cnt>=0){
    if(T[cnt].second>W){
      ans+=T[cnt].first*W;
      break;
    }
    else {
      ans+=T[cnt].first*T[cnt].second;
      W-=T[cnt].second;
    }
    cnt--;
  }
  cout<<ans<<endl;
}