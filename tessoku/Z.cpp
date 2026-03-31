#include<bits/stdc++.h>
using namespace std;

bool sosu(int a){
  bool p=true;
  for(int i=2;i*i<=a;i++)if(a%i==0)p=false;
  return p;
}

int main(){
  int q,i;
  cin>>q;
  int x[q];
  for(i=0;i<q;i++)cin>>x[i];
  
  for(i=0;i<q;i++){
    bool p=sosu(x[i]);
    cout<<(p ? "Yes":"No")<<endl;
  }
}