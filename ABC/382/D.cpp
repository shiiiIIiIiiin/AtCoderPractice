#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<vector<int>> result;

void seq(vector<int> &cur,int pos,int sum){
  if(cur.size()==N){
    result.push_back(cur);
    return;
  }
  
  for(int i=pos;i<=M;i++){
    cur.push_back(i);
    seq(cur,i,sum+i);
    cur.pop_back();
  }
}

int main() {
    cin >> N >> M;
    M=M-(10*N-9);

    vector<int> cur;
    seq(cur, 0,0); // 初期状態で合計は 0
    
    /*
    for(auto r:result){
      for(auto x:r)cout<<x<<" ";
      cout<<endl;
    }
    */
    
    cout<<result.size()<<endl;

    for(int i=0;i<result.size();i++){
      
      for(int j=0;j<N;j++)cout<<1+10*j+result[i][j]<<" ";
      cout<<endl;
    }
    

    return 0;
}