#include<bits/stdc++.h>
using namespace std;

int main(){
 set<int> T;
 int Q;
 cin>>Q;
 int query[Q],x[Q],i;
 for(i=0;i<Q;i++){
   cin>>query[i]>>x[i];
 }
 
 for(i=0;i<Q;i++){
   if(query[i]==1)T.insert(x[i]);
   else if(query[i]==2)T.erase(x[i]);
   else{
     auto itr=T.lower_bound(x[i]);
     if(itr==T.end())cout<<-1<<endl;
     else cout<<(*itr)<<endl;
   }
 }
}