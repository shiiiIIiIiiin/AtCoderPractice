#include<bits/stdc++.h>
using namespace std;

int main(){
  string s,t;
  cin>>s>>t;

  int k=0;
  vector<int> ans(0);
  for(int i=0;i<s.size();i++){
    while(true){
      if(t[k]==s.at(i)){
        ans.push_back(k+1);
        k++;
        break;
    }else {
      k++;
    }
  }
  
  } 

  for(int i:ans){
    cout<<i<<" ";
  }
  cout<<endl;
}