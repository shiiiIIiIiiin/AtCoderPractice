#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
    int N;cin>>N;
    vector<int> A(N);
    for(int i=0;i<N;i++)cin>>A[i];
    cout<<A[0]<<" ";
    for(int i=1;i<N;i++){
        if(abs(A[i-1]-A[i])==1){
            cout<<A[i]<<" ";
            continue;
        }

        if(A[i-1]<A[i]){
            for(int j=A[i-1]+1;j<=A[i];j++)cout<<j<<" ";
        }
        else{
            for(int j=A[i-1]-1;j>=A[i];j--)cout<<j<<" ";
        }
    }
}