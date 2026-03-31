#include <bits/stdc++.h>
using namespace std;

int main() {
  //p^2*q^2 または p^8と表される整数が約数を９個持つ(p,q素数でp!=q)
  
  long long N;cin>>N;
  
  vector<long long> primes;
  
  long long MAX_TEST=1000000;
  
  //エラトステネスの篩でMAX_TEST以下の素数を列挙する
  
  vector<bool> isprime(MAX_TEST+1,true);
  
  for(int i=2;i<=MAX_TEST;i++){
    if(!isprime[i])continue;
    for(int j=2;i*j<=isprime.size();j++)isprime[i*j]=false;
  }
  
  for(int i=2;i<isprime.size();i++)if(isprime[i])primes.push_back(i);
  //ここまでで素数を列挙できた
  
  //10^6以下の素数の数は78498個
  
  
  long long ans=0;
  
  for(int i=0;i<primes.size()-1;i++){
    int l=i,r=primes.size(),m;
    
    if(pow(primes[i],4)>N)break;
    
    while(r-l>1){
      m=(r+l)/2;
      if(primes[i]*primes[i]*primes[m]*primes[m]<=N)l=m;
      else r=m;
    }
    
    ans+=l-i;
  }
  
  
  
  for(int i=0;i<primes.size();i++){
    if(pow(primes[i],8)>N)break;
    ans++;
  }
  
  
  cout<<ans<<endl;
}