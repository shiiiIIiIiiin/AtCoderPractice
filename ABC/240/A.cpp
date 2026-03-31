#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;

int main(){
  int a,b;cin>>a>>b;
  
  if(b==10){
    cout<<(a==1||a==9 ? "Yes":"No")<<endl;
    return 0;
  }
  cout<<(abs(a-b)==1 ? "Yes":"No")<<endl;
}