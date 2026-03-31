#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,K;
  cin>>N>>K;
  
  int i,j,k,ans=0;
  
  for(i=1;i<=N;i++){
    if(K-i>2*N)continue;
    
    for(j=1;j<=N;j++){
     if(K-i-j<=N&&K-i-j>=1)ans++;
    }
  }
  cout<<ans<<endl;
}