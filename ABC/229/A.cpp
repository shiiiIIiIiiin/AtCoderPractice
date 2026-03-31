#include<bits/stdc++.h>
using namespace std;

int main(){
   string S,T;
   cin>>S>>T;

   bool ans;

   ans=(S[0]=='.'&&S[1]=='#'&&T[0]=='#'&&T[1]=='.')||(S[1]=='.'&&S[0]=='#'&&T[1]=='#'&&T[0]=='.');

   cout<<(ans ? "No":"Yes")<<endl;
   
}