#include<bits/stdc++.h>
using namespace std;

int main(){
 string S;
 cin>>S;
 
 bool ok=true;
 
 if(S[0]!='<')ok=false;
 int i=1;
 
 while(true){
   if(S[i]!='='&&S[i]!='>'){
     ok=false;
     break;
   }
   
   if(S[i]=='>')break;
   i++;
 }
 
 
 cout<<(ok&&i==S.size()-1 ? "Yes":"No")<<endl;
 
}