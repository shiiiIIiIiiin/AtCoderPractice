#include<bits/stdc++.h>
using namespace std;

typedef struct P{
  int x,y;
}P;

typedef struct Line{
  P p,q;
}L;

double tim(double a,double b,double c,double d,double t){
  return sqrt((a-c)*(a-c)+(b-d)*(b-d))/t;
}

int main(){
  int N;
  float S,T;
  cin>>N>>S>>T;
  Line L[N];
  
  for(int i=0;i<N;i++)cin>>L[i].p.x>>L[i].p.y>>L[i].q.x>>L[i].q.y;
  
  double ans=1e18;
  
  vector<int> per(N);
  for(int i=0;i<N;i++)per[i]=i;
  
  for(int i=0;i<1<<N;i++){
    
    do{
       double memo=0;
       vector<int> kouho(N,0);
       
       if(i&1<<per[0]){
         memo=tim(0,0,L[per[0]].p.x,L[per[0]].p.y,S)+tim(L[per[0]].p.x,L[per[0]].p.y,L[per[0]].q.x,L[per[0]].q.y,T);
         kouho[per[0]]=0;
       }
       else{
         memo=tim(0,0,L[per[0]].q.x,L[per[0]].q.y,S)+tim(L[per[0]].p.x,L[per[0]].p.y,L[per[0]].q.x,L[per[0]].q.y,T);
         kouho[per[0]]=1;
       }
       
      for(int j=1;j<N;j++){
        int pos=per[j],pre=per[j-1];
        
       if(i&1<<pos){
         kouho[pos]=0;//qで終わる
        if(kouho[pre]){
          memo+=tim(L[pre].p.x,L[pre].p.y,L[pos].p.x,L[pos].p.y,S);
        }else{
          memo+=tim(L[pre].q.x,L[pre].q.y,L[pos].p.x,L[pos].p.y,S);
        }
       }
       else{
          kouho[pos]=1;//pで終わる
          if(kouho[pre]){
            memo+=tim(L[pre].p.x,L[pre].p.y,L[pos].q.x,L[pos].q.y,S);
          }
          else{
            memo+=tim(L[pre].q.x,L[pre].q.y,L[pos].q.x,L[pos].q.y,S);
          }
       }
       memo+=tim(L[pos].p.x,L[pos].p.y,L[pos].q.x,L[pos].q.y,T);
      }
      
      ans=min(ans,memo);
      
    }while(next_permutation(per.begin(),per.end()));
  }
  
  printf("%.10f",ans);
}