#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<string> S(N);
  for(int i=0;i<N;i++)cin>>S[i];
  
  long long ans=0;
  
  int tate[N],yoko[N];
  for(int i=0;i<N;i++)tate[i]=0;
  for(int i=0;i<N;i++)yoko[i]=0;
  
  for(int i=0;i<N;i++)for(int j=0;j<N;j++)if(S[i][j]=='o')yoko[i]++;
  for(int i=0;i<N;i++)for(int j=0;j<N;j++)if(S[j][i]=='o')tate[i]++;
  
  /*
  for(int i=0;i<N;i++)cout<<yoko[i]<<" ";
  cout<<endl;
  for(int i=0;i<N;i++)cout<<tate[i]<<" ";
  cout<<endl;
  */
  
  
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      
      int p=tate[j],q=yoko[i];
     
      if(S[i][j]=='o'){
        ans+=(p-1)*(q-1);//S[i][j]を選ぶ場合
      }
     
      
    }
  }
  
  cout<<ans<<endl;
  
  
}