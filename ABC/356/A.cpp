#include<bits/stdc++.h>
using namespace std;

int main(){
 int N,L,R,i;
 cin>>N>>L>>R;
 
 for(i=0;i<L-1;i++)cout<<i+1<<" ";
 for(i=R;i>=L;i--)cout<<i<<" ";
 for(i=R+1;i<=N;i++)cout<<i<<" ";
}