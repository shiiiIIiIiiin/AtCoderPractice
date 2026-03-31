#include<bits/stdc++.h>
using namespace std;
int main(){
 int K,G,M;
 cin>>K>>G>>M;
 
 int cnt,ng=0,nm=0;
 
 for(cnt=0;cnt<K;cnt++){
   if(ng==G){
     ng=0;
   }else if(nm==0){
     nm=M;
   }else{
     if(G-ng>=nm){
       ng+=nm;
       nm=0;
     }else{
       nm-=G-ng;
       ng=G;
     }
   }
  // cout<<ng<<" "<<nm<<endl;
 }
 
 cout<<ng<<" "<<nm<<endl;
}