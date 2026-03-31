#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<int> A(3*N);
  for(int i=0;i<3*N;i++)cin>>A[i];
  
  vector<vector<int>> num(N+1,vector<int>(0));
  for(int i=0;i<3*N;i++)num[A[i]].push_back(i);
  for(int i=1;i<=N;i++)sort(num[i].begin(),num[i].end());
  vector<pair<int,int>> B(N);
  for(int i=0;i<N;i++)B[i].first=num[i+1][1],B[i].second=i+1;
  sort(B.begin(),B.end());
  
  for(int i=0;i<N;i++)cout<<B[i].second<<" ";
}