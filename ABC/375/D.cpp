#include<bits/stdc++.h>
using namespace std;

int main(){
  string S;
    cin>>S;
    int N=S.size();
    vector<vector<long long>> str(26,vector<long long> (0));

    for(int i=0;i<N;i++)str[(int)(S[i]-'A')].push_back(i);

    long long ans=0;

    for(int i=0;i<26;i++){
        if(str[i].size()<=1)continue;
        for(int j=0;j<str[i].size();j++){
            ans+=str[i][j]*(2*j+1-str[i].size());
        }
        ans-=str[i].size()*(str[i].size()-1)/2;
    }
    cout<<ans<<endl;
}