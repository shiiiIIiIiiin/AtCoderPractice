#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<string> S(N);
  vector<int> A(N);
  for(int i=0;i<N;i++)cin>>S[i]>>A[i];
  
  int m=INT_MAX,k=-1;
  for(int i=0;i<N;i++){
    if(m>A[i])m=A[i],k=i;
  }
  
  for(int i=k;i<N+k;i++){
    cout<<S[i%N]<<endl;
  }
  
  
}