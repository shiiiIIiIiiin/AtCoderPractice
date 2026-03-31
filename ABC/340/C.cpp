#include<bits/stdc++.h>
using namespace std;

map<long long,long long> m;

long long f(long long N){
  if(N==1)return 0;
  if(m.count(N))return m[N];
  
  return m[N]=f(N/2)+f((N+1)/2)+N;
  
}


int main(){
  long long N;cin>>N;
  cout<<f(N)<<endl;
}