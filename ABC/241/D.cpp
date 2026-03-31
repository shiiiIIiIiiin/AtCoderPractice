#include <bits/stdc++.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
using ll = long long;

int main(){
  ll Q;cin>>Q;
  multiset<ll> s;
  
  for(int i=0;i<Q;i++){
    int q;cin>>q;
    
    if(q==1){
      ll x;cin>>x;
      s.insert(x);
    }
    else if(q==2){
      ll x,k;cin>>x>>k;
      auto it=s.upper_bound(x);
      
      bool f=true;
      for(int i=0;i<k;i++){
        if(it==s.begin()){
          cout<<-1<<endl;
          f=false;
          break;
        }
        --it;
      }
      
      if(f)cout<<*it<<endl;
      
    }
    else{
      ll x,k;cin>>x>>k;
      auto it=s.lower_bound(x);
      
      bool f=true;
      
      for(int i=0;i<k-1;i++){
        if(it==s.end()){
          //cout<<-1<<endl;
          f=false;
          break;
        }
        ++it;
      }
      
      if(f&&it!=s.end())cout<<*it<<endl;
      else cout<<-1<<endl;
    }
    
  }
  
}