#include<bits/stdc++.h>
using namespace std;
int main(){
  int N;
  cin>>N;
  int A[N-1],i;
  for(i=0;i<N-1;i++)cin>>A[i];
  
  int ans=0;
  for(i=0;i<N-1;i++)ans-=A[i];
  cout<<ans<<endl;
}