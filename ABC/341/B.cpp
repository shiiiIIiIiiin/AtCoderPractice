#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,i;
  cin>>N;
  
  long long A[N],S[N-1],T[N-1];
  for(i=0;i<N;i++)cin>>A[i];
  for(i=0;i<N-1;i++)cin>>S[i]>>T[i];
  
  for(i=0;i<N-1;i++){
   // int k=A[i]/S[i];
    A[i+1]+=A[i]/S[i]*T[i];
  }
  
  cout<<A[N-1]<<endl;
}