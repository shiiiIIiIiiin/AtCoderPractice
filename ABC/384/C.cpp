#include<bits/stdc++.h>
using namespace std;

int main(){
  int N=5;
  vector<int> points(N);
  for(int i=0;i<N;i++)cin>>points[i];
  
  vector<pair<int,string>> p;
  
  for(int i=0;i<1<<5;i++){
    string name="";
    for(int j=0;j<5;j++){
      if(i & 1<<j)name+=char('A'+j);
    }
    
    long long ans=0;
    
    for(int j=0;j<name.size();j++){
      ans+=points[name[j]-'A'];
    }
    
    p.push_back({ans,name});
    
  }
  
  sort(p.begin(),p.end(),[] (const pair<int,string> &a,const pair<int,string> &b){
    if(a.first!=b.first)return a.first<b.first;
    return a.second>b.second;
  });
  
  for(int i=p.size()-1;i>=0;i--)cout<<p[i].second<<endl;
  
}