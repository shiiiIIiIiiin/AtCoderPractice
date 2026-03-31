#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<int> A(N);
  for(int i=0;i<N;i++)cin>>A[i];
  
  sort(A.begin(),A.end());
  
  
  long long ans=0;
  
  while(A[N-2]!=0){
    A[N-1]--;
    A[N-2]--;
    ans++;
    sort(A.begin(),A.end());
  }
  
  cout<<ans<<endl;
}