#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;

int main(){
  int N;cin>>N;
  set<int> s;
  for(int i=0;i<N;i++){
    int a;cin>>a;
    s.insert(a);
  }
  
  cout<<s.size()<<endl;
}