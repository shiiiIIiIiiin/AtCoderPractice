#include <bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<int> H(N),ans;
  for(int i=0;i<N;i++)cin>>H[i];
  
  stack<int> s;
  s.push(INT_MAX);
  
  for(int i=0;i<N;i++){
    ans.push_back(s.size());
    while(s.top()<=H[N-1-i])s.pop();
    
    s.push(H[N-1-i]);
  }
  
  for(int i=0;i<ans.size();i++)cout<<ans[ans.size()-1-i]-1<<" ";
  
}