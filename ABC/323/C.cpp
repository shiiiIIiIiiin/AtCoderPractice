#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> A(M);
    vector<string> S(N);
    for (int i = 0; i < M; ++i) {
        cin >> A[i];
    }
    for (int i = 0; i < N; ++i) {
        cin >> S[i];
    }
    
    vector<long long> ans(N);
    
    for (int i = 0; i < N; ++i) {
        int point = i + 1; // ボーナスポイント
        for (int j = 0; j < M; ++j) {
            if (S[i][j] == 'o') {
                point += A[j];
            }
        }
        ans[i] = point;
    }
    
    long long max_score = *max_element(ans.begin(), ans.end());
    
    for (int i = 0; i < N; ++i) {
        if (ans[i] == max_score) {
            cout << 0 << endl;
            continue;
        }
        
        vector<int> remaining_problems;
        for (int j = 0; j < M; ++j) {
            if (S[i][j] == 'x') {
                remaining_problems.push_back(A[j]);
            }
        }
        
        sort(remaining_problems.rbegin(), remaining_problems.rend()); // 大きい順にソート
        
        int cnt = 0;
        long long current_score = ans[i];
        
        for (int score : remaining_problems) {
            current_score += score;
            ++cnt;
            if (current_score > max_score) {
                break;
            }
        }
        
        cout << cnt << endl;
    }
    
    return 0;
}