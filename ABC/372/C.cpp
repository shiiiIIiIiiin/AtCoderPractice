#include<bits/stdc++.h>
using namespace std;

int main() {
    int N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;

    int ans = 0;
    
    for (int i = 0; i < N - 2; i++) {
        if (S[i] == 'A' && S[i + 1] == 'B' && S[i + 2] == 'C') {
            ans++;
        }
    }

    for (int i = 0; i < Q; i++) {
        int x;
        char c;
        cin >> x >> c;
        x--;

        if (x - 2 >= 0 && S[x - 2] == 'A' && S[x - 1] == 'B' && S[x] == 'C') {
            ans--;
        }
        if (x - 1 >= 0 && x + 1 < N && S[x - 1] == 'A' && S[x] == 'B' && S[x + 1] == 'C') {
            ans--;
        }
        if (x + 2 < N && S[x] == 'A' && S[x + 1] == 'B' && S[x + 2] == 'C') {
            ans--;
        }

        S[x] = c;

        if (x - 2 >= 0 && S[x - 2] == 'A' && S[x - 1] == 'B' && S[x] == 'C') {
            ans++;
        }
        if (x - 1 >= 0 && x + 1 < N && S[x - 1] == 'A' && S[x] == 'B' && S[x + 1] == 'C') {
            ans++;
        }
        if (x + 2 < N && S[x] == 'A' && S[x + 1] == 'B' && S[x + 2] == 'C') {
            ans++;
        }

        cout << ans << endl;
    }

    return 0;
}