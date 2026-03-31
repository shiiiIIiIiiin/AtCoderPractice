#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,C;cin>>N>>C;
  int cnt=1000000,ans=0;
  vector<int> T(N);
  for(int i=0;i<N;i++)cin>>T[i];
  for(int i=N-2;i>=0;i--)T[i+1]-=T[i];
  
  for(int i=0;i<N;i++){
    if(cnt+T[i]<C)cnt+=T[i];
    else{
      ans++;
      cnt=0;
    }
  }
  
  cout<<ans<<endl;
}