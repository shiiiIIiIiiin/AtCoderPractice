#include<bits/stdc++.h>
using namespace std;

int main(){
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<int>> A(M+1);
    char R[M+1];
    int C[M+1], ans = 0;
  
    for(int i = 1; i <= M; i++){
        cin >> C[i];
        for(int j = 0; j < C[i]; j++){
            int a;
            cin >> a;
            A[i].push_back(a);
        }
        cin >> R[i];
    }
  
    for(int i = 0; i < (1 << N); i++){ // bit全探索
        bool tukau[N+1] = {false};
        int memo = i, cnt = 1;
        while(memo != 0){
            if(memo % 2 == 1) tukau[cnt] = true;
            memo /= 2;
            cnt++;
        }
        
        bool can = true;
        for(int k = 1; k <= M; k++){
            int cnt2 = 0;
            for(int m = 0; m < A[k].size(); m++){
                if(tukau[A[k][m]]) cnt2++;
            }
            
            if(cnt2 >= K && R[k] == 'x') can = false;
            else if(cnt2 < K && R[k] == 'o') can = false;
        }
        
        if(can) ans++;
    }
  
    cout << ans << endl;
}