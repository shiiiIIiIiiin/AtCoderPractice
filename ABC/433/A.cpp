#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll=long long;

int main() {
    ll X,Y,Z;cin>>X>>Y>>Z;

    for(int i=0;i<1e6;i++){
        if((X+i)==Z*(Y+i)){
            cout<<"Yes"<<endl;
            return 0;
        }
    }

    cout<<"No"<<endl;
}