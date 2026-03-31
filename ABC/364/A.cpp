#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  vector<string> S(N);
  for(int i=0;i<N;i++)cin>>S[i];
  
  bool f=false;
  
  for(int i=0;i<N;i++){
    if(S[i][1]=='w'){
      if(f&&i!=N-1){
        cout<<"No"<<endl;
        return 0;
      }
      f=true;
    }
    else{
      f=false;
    }
    
  }
  
  cout<<"Yes"<<endl;
}