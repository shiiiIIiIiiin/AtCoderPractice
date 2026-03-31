#include<bits/stdc++.h>
using namespace std;

int main(void){
  int a,b,ans=0,i;
  
  for(i=0;i<9;i++){
    cin>>a;
    ans+=a;
  }
  
  for(i=0;i<8;i++){
    cin>>b;
    ans-=b;
  }
  
  cout<<ans+1<<endl;
}