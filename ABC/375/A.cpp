#include<bits/stdc++.h>

using namespace std;



int main(){

  int N;

  string S; cin >> N >> S;

  

  int ans = 0;

  

  for (int i = 0; i < N - 2; i++) {

    if (S[i] == '#' && S[i + 1] == '.' && S[i + 2] == '#')ans++;

  }

  

  cout<<ans<<endl;

  

}