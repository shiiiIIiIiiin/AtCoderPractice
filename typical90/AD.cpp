#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,K;cin>>N>>K;
  int cnt[N+1];for(int i=0;i<=N+1;i++)cnt[i]=0;
  
  for(int i=2;i<=N;i++){
     if(cnt[i]!=0)continue;//素数でなければcontinue
     
    for(int j=i;j<=N;j+=i){
      cnt[j]++;
    }
  }
  
  int ans=0;
  for(int i=1;i<=N;i++)if(cnt[i]>=K)ans++;
  cout<<ans<<endl;
}