#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,s=0,i;
  cin>>N;
  int a[N];
  char t[N];
  
  for(i=0;i<N;i++)cin>>t[i]>>a[i];
  
  for(i=0;i<N;i++){
    if(t[i]=='+')s+=a[i];
    if(t[i]=='-')s-=a[i];
    if(t[i]=='*')s*=a[i];
    
    while(s<0){
      s+=10000;
    }
    
    s%=10000;
    cout<<s<<endl;
  }
 
}