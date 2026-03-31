#include <bits/stdc++.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
using ll = long long;

int main(){
  int N;cin>>N;
  
  for(int i=0;i<=25;i++){
    if(N-4*i<0)break;
    
    if((N-4*i)%7==0){
      cout<<"Yes";
      return 0;
    }
  }
  
  cout<<"No";
}