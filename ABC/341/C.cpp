#include<bits/stdc++.h>
using namespace std;
int main(){
  int H,W,N,i,j,k,ans=0;
  string T;
  
  cin>>H>>W>>N;
  cin>>T;
  
  string S[H];
  for(i=0;i<H;i++)cin>>S[i];
  
  for(i=0;i<H;i++){
    for(j=0;j<W;j++){//二重でスタート位置を全探索
    if(S[i][j]=='#')continue;
     bool can=true;
      int I=i,J=j;
      
      for(k=0;k<N;k++){
       if(T[k]=='L')J-=1; 
        if(T[k]=='R')J+=1; 
        if(T[k]=='U')I-=1; 
        if(T[k]=='D')I+=1; 
        
        if(S[I][J]=='#'){
          can=false;
          break;
        }
      }  
      if(can)ans++;
    }
  }
  cout<<ans<<endl;
}