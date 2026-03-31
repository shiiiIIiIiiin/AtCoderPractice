#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,i;
  cin>>N;
  vector<long int> A(N),B(N);
  for(i=0;i<N;i++)cin>>A[i];
  for(i=0;i<N;i++)cin>>B[i];
  
  sort(A.begin(),A.end());
  sort(B.begin(),B.end());
  
  long int sum=0;
  
  for(i=0;i<N;i++)sum+=labs(A[i]-B[i]);
  
  cout<<sum<<endl;
 
}