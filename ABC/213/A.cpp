#include<bits/stdc++.h>
using namespace std;

int main(){
  int A,B;cin>>A>>B;
  
  for(int i=0;i<=255;i++){
    
    int a=A,copy=i;
    int cnt=0,ans=0;
    
    while(a!=0||copy!=0){
      if(a%2!=copy%2)ans+=pow(2,cnt);
      a/=2;
      copy/=2;
      cnt++;
    }
    if(ans==B)cout<<i<<endl;
  }
  
}