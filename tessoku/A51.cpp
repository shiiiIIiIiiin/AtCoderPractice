#include<bits/stdc++.h>
using namespace std;

int main(){
  int Q,i;
  cin>>Q;
  int a[Q];
  string t[Q];
  
  for(i=0;i<Q;i++)t[i]='0';
  for(i=0;i<Q;i++){
    cin>>a[i];
    if(a[i]==1)cin>>t[i];
  }
  
  stack<string> S;
  
  for(i=0;i<Q;i++){
    if(a[i]==1)S.push(t[i]);
    if(a[i]==2)cout<<S.top()<<endl;
    if(a[i]==3)S.pop();
  }
  
}