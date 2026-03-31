#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  string S;cin>>S;
  
  vector<int> te;
  for(int i=0;i<N;i++){
    if(S[i]=='R')te.push_back(0);
    if(S[i]=='P')te.push_back(1);
    if(S[i]=='S')te.push_back(2);
  }
  
  long long dp[3][N];
  
  for(int i=0;i<3;i++)for(int j=0;j<N;j++)dp[i][j]=-100;
  
  for(int i=0;i<3;i++)dp[i][0]=0;
  
  if(S[0]=='R')dp[1][0]=1;
  if(S[0]=='P')dp[2][0]=1;
  if(S[0]=='S')dp[0][0]=1;
  
  
    for(int j=1;j<N;j++){
     for(int i=0;i<3;i++){
      
      long long a=dp[(i+1)%3][j-1],b=dp[(i+2)%3][j-1];
      
      if(te[j]==(i+2)%3){//勝ってるとき
        dp[i][j]=max(a,b)+1;
      }else if(te[j]==(i+1)%3){//負けてるとき
        dp[i][j]=0;
      }else{
        dp[i][j]=max(a,b);
      }
      
      
      
      }
      
    }
    
    long long ans=-1;
    
    for(int i=0;i<3;i++){
      ans=max(dp[i][N-1],ans);
    }
    
    cout<<ans<<endl;
    
  }