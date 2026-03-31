#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<string> S(N);
    for (int i = 0; i < N; i++) cin >> S[i];

    map<string, int> m;

    // 各文字列の出現回数をカウント
    for (int i = 0; i < N; i++) m[S[i]]++;

    vector<pair<int, string>> ans;
    int max_count = -1;

    // 最も出現回数が多い文字列を探す
    for (const auto& s : S) {
        if (m[s] > max_count) {
            ans.clear();
            ans.push_back(make_pair(m[s], s));
            max_count = m[s];
        } else if (m[s] == max_count) {
            ans.push_back(make_pair(m[s], s));
        }
    }

    // 重複を排除して出力
    set<string> unique_strings;
    for (const auto& p : ans) {
        unique_strings.insert(p.second);
    }

    for (const auto& str : unique_strings) {
        cout << str << endl;
    }

    return 0;
}