#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,i;
  string S;
  cin>>N>>S;
  
  set<pair<int,int>> st;
  
  int x=0,y=0;
  
  int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
  st.insert(pair(0,0));
  
  for(i=0;i<N;i++){
    if(S[i]=='R')x+=dx[0];
    else if(S[i]=='L')x+=dx[1];
    else if(S[i]=='U')y+=dy[2];
    else y+=dy[3];
    
    if(st.count(pair(x,y))){
      cout<<"Yes"<<endl;
      return 0;
    }
    
    st.insert(pair(x,y));
    
  }
  
  cout<<"No"<<endl;
}