#include<bits/stdc++.h>
using namespace std;

long long gcd(long long a,long long b){
  if(a%b==0)return b;
  return gcd(b,a%b);
}

int main(){
  long long A,B;cin>>A>>B;
  
  if(1'000'000'000'000'000'000/B<A/gcd(A,B))cout<<"Large"<<endl;
  else cout<<A/gcd(A,B)*B<<endl;
}