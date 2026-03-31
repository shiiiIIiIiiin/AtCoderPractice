#include<bits/stdc++.h>
using namespace std;

int main(){//二次元の累積和を用いる
  long long N,i,j;cin>>N;
  
  long long A[1001][1001];
  for(i=0;i<1001;i++)for(j=0;j<1001;j++)A[i][j]=0;
  
  for(i=0;i<N;i++){
    int a,b,c,d;cin>>a>>b>>c>>d;
    A[a][b]++;A[c][b]--;A[a][d]--;A[c][d]++;
  }
  
  for(i=0;i<1001;i++)for(j=1;j<1001;j++)A[i][j]+=A[i][j-1];
  for(i=0;i<1001;i++)for(j=1;j<1001;j++)A[j][i]+=A[j-1][i];
  
  long long ans[N+1];
  for(i=0;i<=N;i++)ans[i]=0;
  
    for(i=0;i<1001;i++){
      for(j=0;j<1001;j++)ans[A[i][j]]++;
    }
    
    for(i=1;i<=N;i++)cout<<ans[i]<<endl;
}