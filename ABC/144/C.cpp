#include<bits/stdc++.h>
using namespace std;

int main(){
  long long N;cin>>N;
  
  vector<long long> insu;
  
  for(long long i=1;i*i<=N;i++){
    if(N%i==0)insu.push_back(i);
  }
  
  long long m=1'000'000'000'000'000'000'000;
  
  for(auto c:insu){
    m=min(m,N/c+c-2);
  }
  
  cout<<m<<endl;
}