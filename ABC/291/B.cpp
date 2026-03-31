#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,i;
  cin>>N;
  vector<int> X(5*N+1);
  
  for(i=1;i<=5*N;i++)cin>>X[i];
  
  sort(X.begin(),X.end());
  
  float sum=0;
  for(i=N+1;i<=4*N;i++)sum+=X[i];
  
  cout<<sum/(3*N)<<endl;
  
}