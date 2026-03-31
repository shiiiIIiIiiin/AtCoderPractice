#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  int A[N];for(int i=0;i<N;i++)cin>>A[i];
  sort(A,A+N);
  int k=A[N-1];
  
  for(int i=N-1;i>=0;i--){
    if(A[i]!=k){
      cout<<A[i]<<endl;
      return 0;
    }
  }
  
}