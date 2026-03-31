#include<bits/stdc++.h>
using namespace std;

int H,W,N;

void bin(int p,int q,vector<int> &a,vector<int> &b,int &u,int &v){
  int l=0,r=a.size(),m;
  while(r-l>1){
    m=(r+l)/2;
    if(p<a[m])r=m;//a[r]は必ずpより大きい
    else l=m;
  }
  u=l;
  
  l=0,r=b.size();
   while(r-l>1){
    m=(r+l)/2;
    if(q<b[m])r=m;//b[r]は必ずqより大きい
    else l=m;
  }
  v=l;
}

int main(){
  //二分探索で各イチゴがどこのピースにあるかを管理する
  cin>>W>>H>>N;
  vector<int> p(N),q(N);
  for(int i=0;i<N;i++)cin>>p[i]>>q[i];
  int A;cin>>A;
  vector<int> a(A+2);
  for(int i=1;i<=A;i++)cin>>a[i];
  a[0]=0,a[A+1]=INT_MAX;
  int B;cin>>B;
  vector<int> b(B+2);
  for(int i=1;i<=B;i++)cin>>b[i];
  b[0]=0,b[B+1]=INT_MAX;
  
  map<pair<int,int>,int> m;
  
  for(int i=0;i<N;i++){
    int u,v;
    bin(p[i],q[i],a,b,u,v);
    m[make_pair(u,v)]++;
  }
  
  int ansm=INT_MAX,ansM=-1;
  
  for(auto x:m){
    ansm=min(ansm,x.second);
    ansM=max(ansM,x.second);
  }
  
  cout<<(m.size()<(A+1)*(B+1) ? 0:ansm)<<" "<<ansM<<endl;
}