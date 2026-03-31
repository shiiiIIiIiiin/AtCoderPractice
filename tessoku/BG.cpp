#include<bits/stdc++.h>
using namespace std;

class SegmentTree{
  public:
  int dat[300000];
  int siz=1;
  
  void init(int N){
    while(siz<N)siz*=2;
    for(int i=1;i<=2*siz;i++)dat[i]=0;
  }
  
  
  //クエリ1に対する処理
  
  void update(int pos,int x){
    pos=pos+siz-1;
    dat[pos]=x;
    
    while(pos>=2){
      pos/=2;
      dat[pos]=dat[2*pos]+dat[2*pos+1];//変えた
    }
    return;
  }
  
  //クエリ2に対する処理
  
  int query(int l,int r,int a,int b,int u){
    if(b<=l||r<=a)return 0;//変えた
    if(l<=a&&b<=r)return dat[u];
    
    int m=(a+b)/2;
    int ansl=query(l,r,a,m,2*u);
    int ansr=query(l,r,m,b,2*u+1);
    
    return ansl+ansr;//変えた
  }
  
};

int main(){
  int N,Q;cin>>N>>Q;
  SegmentTree SEG;
  SEG.init(N);//初期化
  
  for(int i=0;i<Q;i++){
    int que,pos,x,l,r;cin>>que;
    
    if(que==1){
      cin>>pos>>x;
      SEG.update(pos,x);
    }else{
      cin>>l>>r;
      cout<<SEG.query(l,r,1,SEG.siz+1,1)<<endl;
    }
  }
  
  return 0;
}