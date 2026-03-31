#include<bits/stdc++.h>
#include<atcoder/all>
using namespace atcoder;
using namespace std;

int main(){
  string S;cin>>S;
  vector<int> f(10,0);
  for(int i=0;i<S.size();i++)f[(int)(S[i]-'0')]++;
  
  //for(int i=0;i<3;i++)cout<<f[i]<<" ";
 
 for(int i=1;i<=3;i++){
   if(f[i]!=i){
     cout<<"No"<<endl;
     return 0;
   }
 }
 
 cout<<"Yes"<<endl;
}