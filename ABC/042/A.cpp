#include <bits/stdc++.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
using ll = long long;

int main(){
  vector<int> A(3);
  cin>>A[0]>>A[1]>>A[2];
  sort(A.begin(),A.end());
  
  if(A[0]==5&&A[1]==5&&A[2]==7)cout<<"YES";
  else cout<<"NO";
}