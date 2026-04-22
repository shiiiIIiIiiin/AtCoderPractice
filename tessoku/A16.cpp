#include<bits/stdc++.h>
using namespace std;
int main(){
  int N;
  cin>>N;
  int A[N+1],B[N+1],i;
  for(i=2;i<=N;i++)cin>>A[i];
  for(i=3;i<=N;i++)cin>>B[i];
  
  int d[N+1];
  d[1]=0;
  d[0]=110;
  B[2]=0;
  
  for(i=2;i<=N;i++){
    d[i]=min(d[i-1]+A[i],d[i-2]+B[i]);
  }
  
  cout<<d[N]<<endl;
}