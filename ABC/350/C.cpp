#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<int> A(N);
  for(int i=0;i<N;i++)cin>>A[i];
  vector<int> id(N+1);
  for(int i=0;i<N;i++)id[A[i]]=i;//id[k]...ｋはどこにあるか
  
  vector<pair<int,int>> ans;
  
  for(int i=0;i<N;i++){
    if(A[i]!=i+1){
      
      ans.push_back(pair(i+1,id[i+1]+1));
      id[A[i]]=id[i+1];
      
      swap(A[i],A[id[i+1]]);
      
      id[i+1]=i;
    }
  }
  
  cout<<ans.size()<<endl;
  for(int i=0;i<ans.size();i++)cout<<ans[i].first<<" "<<ans[i].second<<endl;
}