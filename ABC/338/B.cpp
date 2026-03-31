#include <bits/stdc++.h>
using namespace std;

int main(){
  string S;cin>>S;
  int cnt[26];
  for(int i=0;i<26;i++)cnt[i]=0;
  
  for(int i=0;i<S.size();i++)cnt[S[i]-'a']++;
  
  int M=0,I=-1;
  for(int i=0;i<26;i++){
    if(M<cnt[i]){
      M=cnt[i];
      I=i;
    }
  }
  
  cout<<(char)(I+'a')<<endl;
  
}