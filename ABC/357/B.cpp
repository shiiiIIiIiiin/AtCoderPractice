#include<bits/stdc++.h>
using namespace std;

int main(){
  int i;
  string S;
  cin>>S;
  
  int cnt=0;
  
  for(i=0;i<S.size();i++){
    if(S.at(i)>='a'&&S.at(i)<='z')cnt++;
  }
  
  if(cnt<=S.size()/2){
    for(int i=0;i<S.size();i++){
      if(S.at(i)>='a'&&S.at(i)<='z')S.at(i)=char(S.at(i)-'a'+'A');
    }
    }else{
       for(int i=0;i<S.size();i++){
         if(S.at(i)>='A'&&S.at(i)<='Z')S.at(i)=char(S.at(i)+'a'-'A');
    }
  }
  cout<<S<<endl;
}