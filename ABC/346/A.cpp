#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;
  cin>>N;
  int A[N],i;
  for(i=0;i<N;i++)cin>>A[i];
  for(i=0;i<N-1;i++)cout<<A[i]*A[i+1]<<" ";
  
  cout<<endl;
  
}