#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<vector<int>> A(N+1,vector<int>(N+1));

  for(int i=1;i<=N;i++){
    for(int j=1;j<=i;j++)cin>>A[i][j];
  }

  int ans=1;

  for(int i=1;i<=N;i++){
    if(ans>=i)ans=A[ans][i];
    else ans=A[i][ans];
  }
  cout<<ans<<endl;
}