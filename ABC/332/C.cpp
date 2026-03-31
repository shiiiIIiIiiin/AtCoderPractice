#include<bits/stdc++.h>
using namespace std;

int main(){
  int N,M;
  cin>>N>>M;
  string S;
  cin>>S;
  
  vector<int> b(0);
  b.push_back(0);
  
  for(int i=0;i<N;i++){
    if(S[i]=='0')b.push_back(i+1);
  }
  
  //if(b[b.size()-1]!=N-1)
  b.push_back(N+1);
  
  
 // for(int i=0;i<b.size();i++)cout<<b[i]<<" ";
  //cout<<endl;
  
  int Max2=-1,Max=-1;
  
  for(int i=0;i<b.size()-1;i++){
    int count1=0,count2=0;
    for(int j=b[i];j<b[i+1]-1;j++){
      //int count1=0,count2=0;
      if(S[j]=='1')count1++;
      else if(S[j]=='2')count2++;
    }
    
    Max=max(Max,count1+count2);
    Max2=max(Max2,count2);
    
    //cout<<Max<<" "<<Max2<<endl;
    
  }
  
  cout<<max(Max-M,Max2)<<endl;
  
}