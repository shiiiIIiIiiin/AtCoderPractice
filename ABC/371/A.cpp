#include <bits/stdc++.h>
using namespace std;

int main() {
  int cnt[3];for(int i=0;i<3;i++)cnt[i]=0;
  char c;
  
  cin>>c;
  
  if(c=='<')cnt[0]++;
  else cnt[1]++;
  
  cin>>c;
  
  if(c=='<')cnt[0]++;
  else cnt[2]++;
  
  cin>>c;
   if(c=='<')cnt[1]++;
  else cnt[2]++;
  
  for(int i=0;i<3;i++){
    if(cnt[i]==1)cout<<char('A'+i)<<endl;
  }
}
