#include<bits/stdc++.h>
using namespace std;

int l(int a,int b){
  return a*a+b*b;
}

int main(){
  vector<string> S(9);
  for(int i=0;i<9;i++)cin>>S[i];
  
  set<pair<int,int>> p;
  vector<int> x,y;
  for(int i=0;i<9;i++)for(int j=0;j<9;j++)if(S[i][j]=='#'){
    p.insert(make_pair(i,j));
    x.push_back(i);
    y.push_back(j);
  }
  
  int N=x.size();
  int ans=0;
  
  for(int i=0;i<N-2;i++){
    for(int j=i+1;j<N-1;j++){
      for(int k=j+1;k<N;k++){
        int a=x[i],b=y[i],c=x[j],d=y[j],e=x[k],f=y[k];
        
        if((c-a)*(e-a)+(d-b)*(f-b)!=0||l(c-a,d-b)!=l(e-a,f-b))continue;
        
        if(p.count(make_pair(e+c-a,f+d-b)))ans++;
        
      }
    }
  }
  
  cout<<ans<<endl;
}