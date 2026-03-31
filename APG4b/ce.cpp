#include<bits/stdc++.h>
using namespace std;
int main(){
  int N,M;
  cin>>N>>M;
  vector<vector<char>> ans(N,vector<char>(N,'-'));
  vector<int> a(M),b(M);
  for(int i=0;i<M;i++){
    cin>>a.at(i)>>b.at(i);
  }
  
  for(int i=0;i<M;i++){
    ans.at(a.at(i)-1).at(b.at(i)-1)='o';
    ans.at(b.at(i)-1).at(a.at(i)-1)='x';
  }
  
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      cout<<ans.at(i).at(j);
      if(j==N-1)cout<<endl;
      else cout<<" ";
    }
  }
  
}