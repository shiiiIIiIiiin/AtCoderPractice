#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,L;cin>>N>>L;
  int A[N];for(int i=0;i<N;i++)cin>>A[i];
  int ans=0;
  
  for(int i=0;i<N;i++)if(A[i]>=L)ans++;
  
  cout<<ans<<endl;
}