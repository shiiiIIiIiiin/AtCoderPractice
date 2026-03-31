#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<long long> A(N),B(N-1);
  for(int i=0;i<N;i++)cin>>A[i];
  for(int i=0;i<N-1;i++)cin>>B[i];
  
  sort(A.begin(),A.end());
  sort(B.begin(),B.end());
  
  long long cntA=N-1,cntB=N-2,memo=A[0];
  
  while(true){
    
   // cout<<cntA<<" "<<cntB<<endl;
    if(A[cntA]<=B[cntB]){
      cntA--;
      cntB--;
    }
    else{
      memo=A[cntA];
      cntA--;
      if(cntA<cntB){
        cout<<-1<<endl;
        return 0;
      }
    }
    
    if(cntB==-1)break;
  }
  
  cout<<memo<<endl;
  
}