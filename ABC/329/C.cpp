#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;cin>>N;
  string S;cin>>S;
  
  vector<int> cnt(26,0);
  
  for(int i=0;i<N;i++){
    int c=1;
    while(i+1<N&&S[i+1]==S[i]){
      c++;
      i++;
    }
    cnt[int(S[i]-'a')]=max(cnt[int(S[i]-'a')],c);
  }
  
  long long ans=0;
  
  for(int i=0;i<26;i++){
    ans+=cnt[i];
  }
  cout<<ans<<endl;
}