#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
    int N;cin>>N;
    int ca=0,ct=0;
    string S;cin>>S;
    for(int i=0;i<N;i++){
        if(S[i]=='A'){
            ca++;
            if(ca==(N+1)/2){
                cout<<"A"<<endl;
                return 0;
            }
        }
        else{
            ct++;
            if(ct==(N+1)/2){
                cout<<"T"<<endl;
                return 0;
            }
        }
    }
}