#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,M;cin>>N>>M;
  vector<int> A(M+2);
  A[0]=-100,A[M+1]=N+100;
  for(int i=1;i<=M;i++)cin>>A[i];
  
  int cnt=0;
  
  for(int i=1;i<=N;i++){
    while(A[cnt]<i)cnt++;
    cout<<A[cnt]-i<<endl;
  }
  
}