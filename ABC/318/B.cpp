#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
  int N;cin>>N;
  int ans=0;
  
  vector<vector<int>> G(101,vector<int>(101,0));
  for(int q=0;q<N;q++){
    int a,b,c,d;cin>>a>>b>>c>>d;
    
    for(int i=a;i<b;i++)for(int j=c;j<d;j++)G[i][j]++;
  }
  
  for(int i=0;i<101;i++)for(int j=0;j<101;j++)if(G[i][j]>=1)ans++;
  
  cout<<ans<<endl;
}