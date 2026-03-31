#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,M;cin>>N>>M;
  vector<vector<int>> G(N+1);
  vector<int> cnt(N+1,0);
 
  for(int i=0;i<M;i++){
    int a,b;cin>>a>>b;
    G[a].push_back(b);
    G[b].push_back(a);
    cnt[b]++;
  }
  
  queue<int> q;
  for(int i=1;i<=N;i++)if(cnt[i]==0)q.push(i);
  vector<int> ans;
  
  while(!q.empty()){
    int pos=q.front();q.pop();
    ans.push_back(pos);
    
    if(q.size()>=1){
      cout<<"No"<<endl;
      return 0;
    }
    
    for(int i=0;i<G[pos].size();i++){
      cnt[G[pos][i]]--;
      if(cnt[G[pos][i]]==0)q.push(G[pos][i]);
    }
  }
  
  vector<int> ans2(N+1);
  for(int i=0;i<ans.size();i++)ans2[ans[i]]=i+1;
  
  if(ans.size()==N){
    cout<<"Yes"<<endl;
    for(int i=1;i<=N;i++)cout<<ans2[i]<<" ";
  }
  else cout<<"No"<<endl;
 
}