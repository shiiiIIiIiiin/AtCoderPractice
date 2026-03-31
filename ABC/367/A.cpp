#include<bits/stdc++.h>
using namespace std;

int main(){
  int a,b,c;cin>>a>>b>>c;
  
  bool can=true;
  
  if(b>c)c+=24;
  
  for(int i=0;i<=c-b;i++){
    if((i+b)%24==a)can=false;
  }
  
  cout<<(can ? "Yes":"No")<<endl;
}