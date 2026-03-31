#include<bits/stdc++.h>
using namespace std;

int main(){
 int Q;
 cin>>Q;
 int query[Q],y[Q],i;
 string x[Q];
 map<string,int> S;
 
 for(i=0;i<Q;i++){
   cin>>query[i];
   if(query[i]==1){
     cin>>x[i]>>y[i];
     S[x[i]]=y[i];
   }
   else{
     cin>>x[i];
     cout<<S[x[i]]<<endl;
   }
 }
}