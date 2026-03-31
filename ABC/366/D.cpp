#include <bits/stdc++.h>
using namespace std;

long long solve(int a, int b, int c, int d, int e, int f, long long ***WA) {
    long long ans = 0;
    
    ans = WA[b][d][f] - WA[a-1][d][f] - WA[b][c-1][f] - WA[b][d][e-1]
        + WA[a-1][c-1][f] + WA[a-1][d][e-1] + WA[b][c-1][e-1] - WA[a-1][c-1][e-1];
    
    return ans;
}

int main() {
    int N;
    cin >> N;

    int ***A = new int**[N+1];
    for (int i = 0; i <= N; i++) {
        A[i] = new int*[N+1];
        for (int j = 0; j <= N; j++) {
            A[i][j] = new int[N+1];
        }
    }

    long long ***WA = new long long**[N+1];
    for (int i = 0; i <= N; i++) {
        WA[i] = new long long*[N+1];
        for (int j = 0; j <= N; j++) {
            WA[i][j] = new long long[N+1];
            for (int k = 0; k <= N; k++) {
                WA[i][j][k] = 0;
            }
        }
    }
    
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            for (int k = 1; k <= N; k++)
                cin >> A[i][j][k];

    // 累積和の計算
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++) {
                WA[i][j][k] = A[i][j][k]
                            + WA[i-1][j][k]
                            + WA[i][j-1][k]
                            + WA[i][j][k-1]
                            - WA[i-1][j-1][k]
                            - WA[i-1][j][k-1]
                            - WA[i][j-1][k-1]
                            + WA[i-1][j-1][k-1];
            }
        }
    }

    int Q;
    cin >> Q;
    
    for (int i = 0; i < Q; i++) {
        int a, b, c, d, e, f;
        cin >> a >> b >> c >> d >> e >> f;
        
        long long p = solve(a, b, c, d, e, f, WA);
        cout << p << endl;
    }
    
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            delete[] A[i][j];
            delete[] WA[i][j];
        }
        delete[] A[i];
        delete[] WA[i];
    }
    delete[] A;
    delete[] WA;
    
    return 0;
}