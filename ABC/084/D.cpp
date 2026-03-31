#include <bits/stdc++.h>
using namespace std;

bool prime(int n){
  if(n==1)return false;
  
  for(int i=2;i*i<=n;i++){
    if(n%i==0)return false;
  }
  return true;
}

int main(){
  int Q;cin>>Q;
  
  vector<int> cnt(100001,0);
  for(int i=1;i<=100000;i++){
    cnt[i]=cnt[i-1];
    if(prime(i)&&prime((i+1)/2))cnt[i]++;
  }
  
  for(int i=0;i<Q;i++){
    int l,r;cin>>l>>r;
    
    cout<<cnt[r]-cnt[l-1]<<endl;
  }
}