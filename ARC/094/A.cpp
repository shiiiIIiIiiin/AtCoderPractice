#include<bits/stdc++.h>
using namespace std;
int main(){
  int A,B,C;
  cin>>A>>B>>C;
  int a[3]={A,B,C};
  sort(a,a+3);
  a[2]-=a[0];
  a[1]-=a[0];
  
  int ans=0;
  while(a[1]>=2){
    ans++;
    a[1]-=2;
    a[2]-=2;
  }
  
  ans+=a[1]+a[2];
  
  cout<<ans<<endl;
}