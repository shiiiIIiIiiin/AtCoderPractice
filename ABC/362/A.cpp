#include <bits/stdc++.h>
using namespace std;

int main(){
  int R,G,B;
  cin>>R>>G>>B;
  string S;
  cin>>S;
  
  if(S[0]=='R')cout<<min(G,B);
  if(S[0]=='G')cout<<min(R,B);
  if(S[0]=='B')cout<<min(R,G);
}