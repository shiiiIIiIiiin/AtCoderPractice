#include<bits/stdc++.h>
using namespace std;

long long C2(long long n){
  return n*(n-1)/2;
}

int main(){
  int N;cin>>N;
  vector<int> A(N);
  for(int i=0;i<N;i++)cin>>A[i];
  
  vector<vector<int>> id(N+1);
  
  for(int i=0;i<N;i++)id[A[i]].push_back(i);
  for(int i=1;i<=N;i++)id[i].push_back(N);
  
  long long ans=0;
  
  for(int i=1;i<=N;i++){
    long long sum=0;
    int pre=-1;
    for(auto id:id[i]){
      sum+=C2(id-pre);
      pre=id;
    }
    
    ans+=C2(N+1)-sum;
  }
  
  cout<<ans<<endl;
}