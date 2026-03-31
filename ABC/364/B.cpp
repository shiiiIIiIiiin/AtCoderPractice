#include<bits/stdc++.h>
using namespace std;

int main(){
  int H,W;cin>>H>>W;
  int a,b;cin>>a>>b;
  
  char C[H+1][W+1];
  for(int i=1;i<=H;i++)for(int j=1;j<=W;j++)cin>>C[i][j];
  string X;cin>>X;
  
  for(int i=0;i<X.size();i++){
    if(X[i]=='U'&&a!=1&&C[a-1][b]!='#')a--;
    if(X[i]=='D'&&a!=H&&C[a+1][b]!='#')a++;
    if(X[i]=='L'&&b!=1&&C[a][b-1]!='#')b--;
    if(X[i]=='R'&&b!=W&&C[a][b+1]!='#')b++;
  }
  cout<<a<<" "<<b<<endl;
}