#include <bits/stdc++.h>
using namespace std;

int main(){
  vector<string> S(8);
  for(int i=0;i<8;i++)cin>>S[i];
  
  vector<vector<bool>> G(64,vector<bool>(64,true));
  
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      if(S[i][j]=='#'){
        for(int k=0;k<8;k++)G[i][k]=false;
        for(int k=0;k<8;k++)G[k][j]=false;
      }
    }
  }
  
  int ans=0;
  
  for(int i=0;i<8;i++)for(int j=0;j<8;j++)if(G[i][j])ans++;
  
  cout<<ans<<endl;
}