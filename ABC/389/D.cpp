#include <bits/stdc++.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
using ll = long long;

int main(){
  ll R;cin>>R;
  
  ll cnt=0;
  
  for(int y=R-1;y>=1;y--){
    double memo=sqrt(R*R-(y+0.5)*(y+0.5))-0.5;
    int k=int(memo);
    //cout<<k<<endl;
    
    if(sqrt(R*R-(y+0.5)*(y+0.5))>=0.5)k++;
    
    cnt+=2*k-1;
  }
  
  cnt*=2;
  
  int memo=int(sqrt(R*R-0.5*0.5)-0.5);
  if(sqrt(R*R-0.5*0.5)>=0.5)memo++;
  
  cnt+=memo*2-1;
  
  cout<<cnt;
}