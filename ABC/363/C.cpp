#include<bits/stdc++.h>
using namespace std;

bool isPalindrome(const string& str, int start, int k) {
    for (int i=0;i <k/2; ++i) {
        if (str[start + i]!=str[start+k-1-i]) {
            return false;
        }
    }
    return true;
}

int main() {
    long long N, K;
    cin>>N>>K;
    string S;
    cin>>S;

    if (K > N) {
        cout << 0 << endl;
        return 0;
    }

    long long ans = 0;
    set<string> seen;

    sort(S.begin(), S.end());
    do {
        bool hasPalindrome = false;
        for (int i = 0; i <= N - K; ++i) {
            if (isPalindrome(S, i, K)) {
                hasPalindrome = true;
                break;
            }
        }
        if (!hasPalindrome) {
            if (seen.find(S) == seen.end()) {
                ans++;
                seen.insert(S);
            }
        }
    } while (next_permutation(S.begin(), S.end()));

    cout << ans << endl;
}