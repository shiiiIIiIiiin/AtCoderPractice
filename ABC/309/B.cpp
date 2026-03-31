#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
  
  int N;cin>>N;
  
  vector<string> A(N);
  for(int i=0;i<N;i++)cin>>A[i];

  cout<<A[1][0];
  for(int i=0;i<N-1;i++)cout<<A[0][i];
  cout<<endl;

  for(int i=1;i<N-1;i++){
    for(int j=0;j<N;j++){
      if(j==0)cout<<A[i+1][0];
      else if(j==N-1)cout<<A[i-1][N-1];
      else cout<<A[i][j];
      if(j==N-1)cout<<endl;
    }
  }

  for(int i=1;i<N;i++)cout<<A[N-1][i];
  cout<<A[N-2][N-1];
  
}