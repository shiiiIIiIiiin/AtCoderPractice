#include<bits/stdc++.h>
using namespace std;

int main(){
  string S,T;
  cin>>S>>T;
  
  int cnt=0;
  
  if(T[2]=='X'){//二つのうちどっちもあり得る
    
    for(int i=0;i<S.size();i++){
      if(S[i]-'a'==T[cnt]-'A'){
        cnt++;
        if(cnt==2){
          cout<<"Yes"<<endl;
          return 0;
        }
      }
    }
    cout<<"No"<<endl;
    return 0;
  }
  else{
    for(int i=0;i<S.size();i++){
      if(S[i]-'a'==T[cnt]-'A'){
        cnt++;
        if(cnt==3){
          cout<<"Yes"<<endl;
          return 0;
        }
      }
    }
    cout<<"No"<<endl;
    return 0;
  }
  
}