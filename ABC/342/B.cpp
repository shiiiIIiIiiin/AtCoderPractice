#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;
  cin>>N;
  int P[N],Q,i,j;
  for(i=0;i<N;i++)cin>>P[i];
  cin>>Q;
  int A[Q],B[Q];
  for(i=0;i<Q;i++)cin>>A[i]>>B[i];
  
  for(i=0;i<Q;i++){
    for(j=0;j<N;j++){
      if(P[j]==A[i]){
        cout<<A[i]<<endl;
        break;
      }
      if(P[j]==B[i]){
        cout<<B[i]<<endl;
        break;
      }
    }
  }
  
  
}