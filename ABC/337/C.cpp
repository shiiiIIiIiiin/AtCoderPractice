#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;
  cin>>N;
  int A[N+1],i;
  
  for(i=1;i<N+1;i++)cin>>A[i];
  
  map<int,int> a;
  
  for(i=1;i<=N;i++)a[A[i]]=i;
  
  cout<<a[-1]<<" ";
  
  int num=a[-1];
  for(i=1;i<N;i++){
    cout<<a[num]<<" ";
    num=a[num];
  }
}