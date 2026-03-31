#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,M;cin>>N>>M;
  int A[M];for(int i=0;i<M;i++)cin>>A[i];
  int cnt[N+1];for(int i=0;i<=N;i++)cnt[i]=0;
  pair<int,int> ans(pair(-1,1000000000));
  
  for(int i=0;i<M;i++){
    cnt[A[i]]++;
    if(cnt[A[i]]>ans.first||(cnt[A[i]]==ans.first&&A[i]<ans.second)){
      ans.first=cnt[A[i]];
      ans.second=A[i];
    }
    cout<<ans.second<<endl;
  }
  return 0;
}