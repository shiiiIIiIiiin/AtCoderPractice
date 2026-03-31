#include<bits/stdc++.h>
using namespace std;

int main(){
  int H,W;
  cin>>H>>W;
  
  char c[H][W];
  long long dp[H][W];
  
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++){
      cin>>c[i][j];
      dp[i][j]=0;
    }
  }
  
  for(int i=0;i<W;i++){
    if(c[0][i]=='#')break;
    else dp[0][i]=1;
  }
  
  for(int i=0;i<H;i++){
    if(c[i][0]=='#')break;
    else dp[i][0]=1;
  }
  
  for(int i=1;i<H;i++){
    for(int j=1;j<W;j++){
      if(c[i-1][j]=='.')dp[i][j]+=dp[i-1][j];
      if(c[i][j-1]=='.')dp[i][j]+=dp[i][j-1];
    }
  }
  
  cout<<dp[H-1][W-1]<<endl;
  
  
}