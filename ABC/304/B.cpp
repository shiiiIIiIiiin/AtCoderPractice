#include<bits/stdc++.h>
using namespace std;

int main(){
  string S;cin>>S;
  int N=S.size();
  for(int i=0;i<3&&i<N;i++)cout<<S[i];
  for(int i=0;i<N-3;i++)cout<<0;
}