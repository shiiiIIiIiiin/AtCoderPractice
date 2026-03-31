#include<bits/stdc++.h>
using namespace std;
int main(){
  string S;
  cin>>S;
  vector<int> c(128);
  
  for(char s:S){
    c[s]++;
  }
  
  //for(int i=0;i<128;i++)cout<<i<<":"<<c[i]<<endl;
  
  vector<int> d(128);
  for(int i=0;i<128;i++)d[i]=0;
   
  for(int i=0;i<128;i++){
    d[c[i]]++;
    //cout<<d[0]<<endl;
  }
  bool ans=true;
  
  for(int i=1;i<128;i++){
    ans&=d[i]==0||d[i]==2;
  }
  cout<<(ans?"Yes":"No")<<endl;
}