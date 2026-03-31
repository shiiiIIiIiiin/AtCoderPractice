#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,Q;
  cin>>N>>Q;
  
  vector<pair<int,int>> ryu;
  int sippo=0,atama=N-1;
  
  for(int i=N;i>0;i--)ryu.push_back(pair(i,0));
  
  for(int i=0;i<Q;i++){
    int q;
    string C;
    cin>>q>>C;
    
    if(q==1){//クエリ1
      int dx=0,dy=0;
      if(C=="R")dx++;
      else if(C=="L")dx--;
      else if(C=="U")dy++;
      else dy--;
      
      ryu.push_back(pair(ryu[atama].first+dx,ryu[atama].second+dy));
      
      sippo++;
      atama++;
    }
    else{//クエリ２
      int k=stoi(C);
      
      cout<<ryu[atama-k+1].first<<" "<<ryu[atama-k+1].second<<endl;
    }
  }
  return 0;
}