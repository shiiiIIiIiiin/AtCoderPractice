#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,M;
  cin>>N>>M;
  int H[N];
  for(int i=0;i<N;i++)cin>>H[i];
  
  int ans=0,sum=0,cnt=0;
  while(sum<=M){
    sum+=H[cnt];
    ans++;
    cnt++;
  }
  
  cout<<ans-1<<endl;
}