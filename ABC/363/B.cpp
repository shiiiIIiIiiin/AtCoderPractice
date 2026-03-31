#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,T,P;
  cin>>N>>T>>P;
  vector<int> L(N);
  for(int i=0;i<N;i++)cin>>L[i];
  
  sort(L.begin(),L.end());
  
  int cnt=0,k=N-1;
  
  while(L[k]>=T){
    cnt++;
    k--;
  }
  
  if(cnt>=P)cout<<0<<endl;
  else cout<<T-L[N-P]<<endl;
  
}