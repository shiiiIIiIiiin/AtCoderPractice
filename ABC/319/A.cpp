#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
  string S;cin>>S;
  map<char,int> m;
  
  m['t']=3858;
  m['k']=3679;
  m['B']=3658;
  m['U']=3648;
  m['a']=3638;
  m['S']=3630;
  m['e']=3613;
  m['m']=3555;
  m['n']=3516;
  m['s']=3481;
  
  cout<<m[S[0]]<<endl;
  
}