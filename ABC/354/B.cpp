#include<bits/stdc++.h>
using namespace std;
int main(){
  int N,i;
  cin>>N;
  vector<string> S(N);
  vector<int> C(N);
  
  for(i=0;i<N;i++)cin>>S[i]>>C[i];
  
  int sum=0;
  for(i=0;i<N;i++)sum+=C[i];
  
  sort(S.begin(),S.end());
  
  sum%=N;
  
  cout<<S.at(sum)<<endl;
}