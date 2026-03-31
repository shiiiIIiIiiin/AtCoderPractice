#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;

int kake(int a,int b){
  int res=1;
  for(int i=0;i<b;i++)res*=a;
  return res;
}

int main(){
  int A,B;cin>>A>>B;
  cout<<kake(A,B)+kake(B,A)<<endl;
}