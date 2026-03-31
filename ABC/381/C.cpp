#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;

int main(){
  long long N;cin>>N;
  string S;cin>>S;
  vector<int> ids;
  for(int i=0;i<N;i++)if(S[i]=='/')ids.push_back(i);
  
  int ans=-1;
  
  for(int i=0;i<ids.size();i++){
    int cnt=1;
    while(true){
      if(ids[i]+cnt>=N||ids[i]-cnt<0||S[ids[i]-cnt]!='1'||S[ids[i]+cnt]!='2')break;
      cnt++;
    }
    ans=max(ans,2*(cnt-1)+1);
  }
  
  cout<<ans<<endl;
}