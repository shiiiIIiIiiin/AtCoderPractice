#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a,long long b){
  if(b==0)return a;
  else return gcd(b,a%b);
}

long long lcm(long long a,long long b){
  return a/gcd(a,b)*b;
}

int main() {
  long long N,M,K;cin>>N>>M>>K;
  long long c=lcm(N,M);
  long long l=0,r=LLONG_MAX,m;
  
  while(r-l>1){
    m=(r+l)/2;
    long long p=m/N+m/M-2*(m/c);
    
    if(p>=K)r=m;
    else l=m;
    
  }
  
  /*
  m=max(m-m%N,m-m%M);
  
  /*
  cout<<m-m%N<<endl;
  cout<<m-m%M<<endl;
  */

  cout<<r<<endl;
}