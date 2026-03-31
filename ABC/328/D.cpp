#include<bits/stdc++.h>
using namespace std;

int main(){
  string S;cin>>S;
  vector<char> st;
  
  for(int i=0;i<S.size();i++){
    st.push_back(S[i]);
    if(st.size()<3)continue;
    
    int n=st.size();
    if(st[n-3]=='A'&&st[n-2]=='B'&&st[n-1]=='C')for(int k=0;k<3;k++)st.pop_back();
  }
  
  for(int i=0;i<st.size();i++)cout<<st[i];
}