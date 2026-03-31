#include<bits/stdc++.h>
using namespace std;
int main(){
  int N,i;
  cin>>N;
  int a[N];
  for(i=0;i<N;i++)cin>>a[i];
  
  int count=0;
  for(i=0;i<N;i++)if(a[i]%2==1)count++;
  
  
  if(count%2==0)cout<<"YES"<<endl;
  else cout<<"NO"<<endl;
  
}