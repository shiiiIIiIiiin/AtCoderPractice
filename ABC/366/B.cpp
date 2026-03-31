#include<bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<string> S(N);
    for(int i = 0; i < N; i++) cin >> S[i];
    
    int M = -1;
    for(int i = 0; i < N; i++) M = max(M, (int)S[i].size());
    
    
    vector<string> ans(M);

    for(int i=0;i<N;i++){
      
      for(int j=0;j<S[N-1-i].size();j++){
        ans[j].push_back(S[N-1-i][j]);
      }
      
      for(int j=0;j<M-S[N-i-1].size();j++){
        ans[j+S[N-i-1].size()].push_back('*');  
      }
      
      /*
      for(int k=0;k<N;k++){
        for(int l=0;l<ans[k].size();l++)cout<<ans[k][l];
        cout<<endl;
      }
      
      cout<<endl;
      
      */
    }
    
    
    for(int i=0;i<M;i++){
      int k=ans[i].size()-1;
      while(ans[i][k]=='*'){
        ans[i].pop_back();
        k--;
      }
    }
    
    
    for(int i=0;i<M;i++)cout<<ans[i]<<endl;
}