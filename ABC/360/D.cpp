#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,T,i;
  cin>>N>>T;
  string S;
  cin>>S;
  vector<int> X(N);
  for(i=0;i<N;i++)cin>>X[i];
  
  vector<int> pst,ngt;//正方向に進むアリと負方向に進むアリを分ける
  
  for(i=0;i<S.size();i++){
    if(S[i]=='0')ngt.push_back(X[i]);
    else pst.push_back(X[i]);
  }
  
  sort(pst.begin(),pst.end());
  sort(ngt.begin(),ngt.end());
  
  long long ans=0;
  
  for(i=0;i<pst.size();i++){
    //正方向のありがすれ違う数を二分探索で求める
    
    //まず最初の時点で自分より負の方向にいる負の方向を向いているありの数を求める
    //ngtに含まれる値のうちpst[i]より小さいものの数を答える
    
    int l=-1,r=ngt.size();//ngt[l]は必ずpst[i]より小さく、ngt[r]は必ずpst[i]より大きいとなるようにする
    
    while(r-l>1){
      int m=(r+l)/2;
      
      if(ngt[m]<pst[i])l=m;
      else r=m;
    }
    
    
    int memo=l;
    //ここまでで移動前の自分のすぐ後ろにいる負方向を向いたありの番号(memo)を調べた
    
    
    
    //次に移動後のありについて考える
      l=-1,r=ngt.size();//ngt[l]-Tは必ずpst[i]+T+0.5より小さく、ngt[r]-Tは必ずpst[i]+T+0.5より大きいとなるようにする
    
    while(r-l>1){
      int m=(r+l)/2;
      
      if(ngt[m]-T<pst[i]+T+0.5)l=m;
      else r=m;
      
    }
    int memo2=l;
    //ここまでで移動後の自分のすぐ後ろにいる負方向を向いたありの番号(memo2)を求めた
    
    ans+=memo2-memo;
  }
  
  cout<<ans<<endl;
}