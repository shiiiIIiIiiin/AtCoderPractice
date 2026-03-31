#include<bits/stdc++.h>
using namespace std;

long long solve(const vector<vector<int>>& G, const vector<vector<int>>& H, const vector<int>& P, const vector<vector<int>>& A) {
    long long cost = 0;
    
    int N = P.size();
    
    for(int i = 0; i < N; i++) {
        for(int j = i+1; j < N; j++) {
            if(G[i+1][j+1] != H[P[i]][P[j]]) {
                cost += A[min(P[i], P[j])][max(P[i], P[j])];
            }
        }
    }
    
    return cost;
}

int main() {
    int N;
    cin >> N;
    
    int MG, MH;
    cin >> MG;
  
    vector<vector<int>> G(N+1, vector<int>(N+1, 0));
    for(int i = 0; i < MG; i++) {
        int u, v;
        cin >> u >> v;
        G[u][v] = 1;
        G[v][u] = 1;
    }

    cin >> MH;
    vector<vector<int>> H(N+1, vector<int>(N+1, 0));
    for(int i = 0; i < MH; i++) {
        int a, b;
        cin >> a >> b;
        H[a][b] = 1;
        H[b][a] = 1;
    }

    vector<vector<int>> A(N+1, vector<int>(N+1));
    for(int i = 1; i < N; i++) {
        for(int j = i+1; j <= N; j++) {
            cin >> A[i][j];
        }
    }

   
    vector<int> P(N);
    iota(P.begin(), P.end(), 1);

    long long min_cost = LLONG_MAX;
    
    do {
        min_cost = min(min_cost, solve(G, H, P, A));
    } while(next_permutation(P.begin(), P.end()));

    cout << min_cost << endl;
    
    return 0;
}