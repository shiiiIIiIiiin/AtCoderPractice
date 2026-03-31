#include<bits/stdc++.h>
using namespace std;
int main(){
  int H,W,N;
  cin>>H>>W>>N;
  vector<int> A(N+1),B(N+1),C(N+1),D(N+1);
  for(int i=1;i<=N;i++)cin>>A[i]>>B[i]>>C[i]>>D[i];
  
  int F[H+2][W+2];
  for(int i=0;i<=H+1;i++){
    for(int j=0;j<=W+1;j++){
      F[i][j]=0;
    }
  }
  
  for(int i=1;i<=N;i++){
    F[A[i]][B[i]]++;
    F[A[i]][D[i]+1]--;
    F[C[i]+1][B[i]]--;
    F[C[i]+1][D[i]+1]++;
  }
  
  for(int i=1;i<=H;i++){
    for(int j=1;j<W;j++){
      F[i][j+1]+=F[i][j];
    }
  }
  
  for(int i=1;i<=W;i++){
    for(int j=1;j<H;j++){
      F[j+1][i]+=F[j][i];
    }
  }
  
  for(int i=1;i<=H;i++){
    for(int j=1;j<=W;j++){
      cout<<F[i][j]<<" ";
    }
    cout<<endl;
  }
  
}