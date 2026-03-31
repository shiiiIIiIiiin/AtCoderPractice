#include<bits/stdc++.h>
using namespace std;

using ll=long long;

ll power(ll A,ll n){
  ll res=1;
  for(int i=0;i<n;i++)res*=A;
  return res;
}

int main(){
  ll B;cin>>B;
  
  for(ll A=1;A<=20;A++){
    ll k=power(A,A);
    if(k>B)break;
    if(k==B){
      cout<<A<<endl;
      return 0;
    }
    
  }
  
  cout<<-1<<endl;
}