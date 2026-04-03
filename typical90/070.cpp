#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<long long> X(N),Y(N);
  for(int i=0;i<N;i++)cin>>X[i]>>Y[i];
  
  sort(X.begin(),X.end());
  sort(Y.begin(),Y.end());
  
  int x=X[(N)/2],y=Y[(N)/2];
  long long ans=0;
  
  for(int i=0;i<N;i++)ans+=labs(x-X[i])+labs(y-Y[i]);
  
  cout<<ans<<endl;
}