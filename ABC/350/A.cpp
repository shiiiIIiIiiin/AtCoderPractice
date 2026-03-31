#include<bits/stdc++.h>
using namespace std;

int main(){
  char S[3];
  for(int i=0;i<3;i++)cin>>S[i];
  
  bool can=true;
  if(S[0]!='A'||S[1]!='B'||S[2]!='C')can=false;
  
  int k;
  cin>>k;
  //cout<<k<<endl;
  
  if(k>349||k==316||k<1)can=false;
  cout<<(can?"Yes":"No")<<endl;
}