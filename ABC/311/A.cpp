#include<bits/stdc++.h>
using namespace std;

int main(){
  int N;
  string S;
  cin>>N>>S;
  
  bool f[3];for(int i=0;i<3;i++)f[i]=false;
  
  for(int i=0;i<S.size();i++){
    int k=S[i]-'A';
    f[k]=true;
    
    for(int j=0;j<3;j++){
      if(!f[j])break;
      if(j==2){
        cout<<i+1<<endl;
        return 0;
      }
    }
  }
  return 0;
}