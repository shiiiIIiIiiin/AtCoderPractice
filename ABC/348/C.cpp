#include<bits/stdc++.h>
using namespace std;
int main(){
  int N;
  cin>>N;
  int A[N],C[N],i;
  for(i=0;i<N;i++)cin>>A[i]>>C[i];
  
  map<int,int> taste_min;
  for(i=0;i<N;i++)taste_min[C[i]]=1000000010;
  for(i=0;i<N;i++)taste_min[C[i]]=min(taste_min[C[i]],A[i]);
  int ans=-1;
  for(i=0;i<N;i++)ans=max(ans,taste_min[C[i]]);
  cout<<ans<<endl;
  
}
