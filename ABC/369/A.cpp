#include <bits/stdc++.h>
using namespace std;

int main() {
  int a,b;cin>>a>>b;
  if(a==b){
    cout<<1<<endl;
    return 0;
  }
  if((a-b)%2==0){
    cout<<3<<endl;
  }
  else{
    cout<<2<<endl;
  }
  return 0;
}