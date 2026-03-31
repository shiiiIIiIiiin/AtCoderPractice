#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;cin>>N;
  int A[N];
  char S[N];
  for(int i=0;i<N;i++)cin>>A[i]>>S[i];
  
  int l=-1,r=-1,ans=0;
  
  for(int i=0;i<N;i++){
    if(S[i]=='L'){
      if(l==-1)l=A[i];
      ans+=abs(l-A[i]);
      l=A[i];
    }else{
      if(r==-1)r=A[i];
      ans+=abs(r-A[i]);
      r=A[i];
    }
  }
  
  cout<<ans<<endl;
}