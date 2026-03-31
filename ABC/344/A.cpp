#include<bits/stdc++.h>
using namespace std;

int main(){
 string S;
 cin>>S;
 
 int i,c=0,a[2];
 
 for(i=0;i<S.size();i++){
   if(S[i]=='|'){
     a[c]=i;
     c++;
   }
 }
 
 for(i=0;i<S.size();i++){
   if(i<a[0]||a[1]<i)cout<<S[i];
 }
 cout<<endl;
}