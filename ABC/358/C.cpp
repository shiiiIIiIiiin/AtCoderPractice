#include<bits/stdc++.h>
using namespace std;
int main(){
  int N,M;
  cin>>N>>M;
  vector<string> S(N);
  int i,j;
  for(i=0;i<N;i++)cin>>S[i];
  
  int scale=(1<<N);
  int ans=1000;
  
  for(i=0;i<scale;i++){
    bool buy[M];
    for(j=0;j<M;j++)buy[j]=false;
    int k=i;
    int cnt=0,p=0;
    
    while(k!=0){
      if(k%2==1){
        cnt++;
        for(j=0;j<M;j++)if(S[p][j]=='o')buy[j]=true;
      }
      p++;
      k/=2;
      
    }
    bool can=true;
    
    for(j=0;j<M;j++)if(buy[j]==false)can=false;
    
    if(can){
      if(cnt<ans)ans=cnt;
    }
    
  }
  
  cout<<ans<<endl;
  
  
}