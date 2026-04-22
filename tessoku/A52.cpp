#include<bits/stdc++.h>
using namespace std;

int main(){
 int Q;
 cin>>Q;
 int query[Q];
 string x[Q];
 for(int i=0;i<Q;i++){
   cin>>query[i];
   if(query[i]==1)cin>>x[i];
 }
 
 queue<string> T;
 
 for(int i=0;i<Q;i++){
   if(query[i]==1) T.push(x[i]);
   else if(query[i]==2)cout<<T.front()<<endl;
   else if(query[i]==3)T.pop();
 }
}