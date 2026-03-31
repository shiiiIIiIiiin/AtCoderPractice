#include <bits/stdc++.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
using ll = long long;

int main(){
  int N,L;cin>>N>>L;
  vector<string> S(N);
  for(int i=0;i<N;i++)cin>>S[i];
  
  sort(S.begin(),S.end());
  
  for(int i=0;i<N;i++)cout<<S[i];
}