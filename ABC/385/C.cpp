#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
  int N;cin>>N;
  vector<int> H(N);
  for(int i=0;i<N;i++)cin>>H[i];
  
  vector<vector<int>> m(3001,vector<int>(0));
  vector<set<int>> st(3001);
  for(int i=0;i<N;i++)m[H[i]].push_back(i);
  for(int i=0;i<=3000;i++){
    for(int j=0;j<m[i].size();j++)st[i].insert(m[i][j]);
  }
  
  
  int ans=-1;
  
  for(int i=1;i<=3000;i++){
    //int cnt=0;
    if(m[i].size()==0)continue;
    if(m[i].size()==1){
      ans=max(ans,1);
    }
    
    for(int l=0;l<m[i].size()-1;l++){
      for(int r=l+1;r<m[i].size();r++){
        
        int w=m[i][r]-m[i][l];//幅wで探索
        int cnt=0,k=0;
        
        while(true){
          if(st[i].count(m[i][l]+k*w)){
            cnt++;
            k++;
          }
          
          else break;
          
        }
        
        ans=max(ans,cnt);
        
      }
    }
    
  }
  
  cout<<ans<<endl;
  
}