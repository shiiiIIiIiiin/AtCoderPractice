#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,M,H,K;cin>>N>>M>>H>>K;
  string S;cin>>S;
  set<pair<int,int>> s;
  for(int i=0;i<M;i++){
    int x,y;cin>>x>>y;
    s.insert(make_pair(x,y));
  }
  
  int posx=0,posy=0;
  
  for(int i=0;i<N;i++){
    if(S[i]=='R')posx++;
    if(S[i]=='L')posx--;
    if(S[i]=='U')posy++;
    if(S[i]=='D')posy--;
    
    H--;
    if(H<0){
      cout<<"No"<<endl;
      return 0;
    }
    
    if(s.count(make_pair(posx,posy))&&H<K){
      s.erase(pair(posx,posy));
      H=K;
    }
    
  }
  
  cout<<"Yes"<<endl;
}