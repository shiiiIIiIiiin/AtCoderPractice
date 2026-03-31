#include<bits/stdc++.h>
using namespace std;

string S;

int main(){
  cin>>S;
  
  set<string> st;
  int i,j;
  for(i=0;i<S.size();i++){
    for(j=1;i+j<=S.size();j++){
      st.insert(S.substr(i,j));
    }
  }
  cout<<st.size()<<endl;
}