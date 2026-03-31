#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
  int K;
  string S,T;
  cin>>K>>S>>T;
  
  if(S.size()>T.size())swap(S,T);//|S|<|T|である
  
  bool ans=false;
  
  if(S.size()==T.size()){//３つ目と完全一致の場合
    int cnt=0;
    for(int i=0;i<S.size();i++)if(S[i]!=T[i])cnt++;
    
    if(cnt<=1)ans=true;
  }
  
  else{
    if(T.size()-S.size()!=1){//大きさの差が２以上ならダメ
      cout<<"No"<<endl;
      return 0;
    }
    
    
    int id=0,cnt=0;
    for(int i=0;i<S.size();i++){//Sに足す場合
      if(S[i]!=T[id]){
        if(cnt!=0){
          cout<<"No"<<endl;
          return 0;
        }
        else {
          cnt++;
          id++;
        }
      }
      id++;
    }
    
    id=0,cnt=0;
    
    for(int i=0;i<S.size();i++){
      if(S[i]!=T[id]){
        if(cnt!=0){
          cout<<"No"<<endl;
          return 0;
        }
        else{
          cnt++;
          i--;
        }
      }
      id++;
    }
    
    
    ans=true;
  }
  
  cout<<(ans ? "Yes":"No")<<endl;
}