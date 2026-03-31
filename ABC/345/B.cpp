#include<bits/stdc++.h>
using namespace std;

int main(){
  long long X;cin>>X;
  if(X%10==0){
    cout<<X/10<<endl;
    return 0;
  }
  
  if(X>0)X+=10;
  
  cout<<X/10<<endl;
  
}