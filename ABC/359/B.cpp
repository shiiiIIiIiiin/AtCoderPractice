#include<bits/stdc++.h>
using namespace std;


int main(void){
  int ans=0;
  int N,i;
  cin>>N;
  int a[2*N];
  
  for(i=0;i<2*N;i++)cin>>a[i];
  
  for(i=0;i<2*N-2;i++){
    if(a[i]==a[i+2])ans++;
  }
  cout<<ans<<endl;
}