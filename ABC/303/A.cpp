#include<bits/stdc++.h>
using namespace std;

bool sim(char a,char b){
  return (a==b||a=='1'&&b=='l'||a=='0'&&b=='o');
}

int main(){
  int N;cin>>N;
  string S,T;cin>>S>>T;
  
  for(int i=0;i<N;i++){
    if(!sim(S[i],T[i])&&!sim(T[i],S[i])){
      cout<<"No"<<endl;
      return 0;
    }
  }
  
  cout<<"Yes"<<endl;
}