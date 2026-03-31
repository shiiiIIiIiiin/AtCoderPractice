#include<iostream>
#include<vector>
using namespace std;
using ll = long long;

ll solve(vector<pair<ll, ll>>& vitamins, ll target) {
    ll max_cal = 5000;
    vector<ll> dp(max_cal + 1, 0);

    for (auto& item : vitamins) {
        ll a = item.first; // 価値
        ll c = item.second; // カロリー
        for (ll j = max_cal; j >= c; j--) {
            dp[j] = max(dp[j], dp[j - c] + a);
        }
    }

    for (ll c = 0; c <= max_cal; c++) {
        if (dp[c] >= target) {
            return c;
        }
    }

    return -1;//target以上の価値は達成不可能
}

int main() {
    ll N, X; 
    cin >> N >> X;
    vector<ll> V(N), A(N), C(N);

    for (int i = 0; i < N; i++) {
        cin >> V[i] >> A[i] >> C[i];
    }

    vector<vector<pair<ll, ll>>> vitamins(3);

    for (int i = 0; i < N; i++) {
        vitamins[V[i] - 1].push_back({A[i], C[i]});
    }

    //決め打ち二分探索で、全てのビタミンをmだけ接種できるか考える
    ll l = -1, r = 1e10, m;

    while (r - l > 1) {
        m = (r + l) / 2;

        ll total_calories = 0;
        bool can = true;

        for (int i = 0; i < 3; i++) {
            ll cal = solve(vitamins[i], m);
            if (cal == -1) {
                can = false;
                break;
            }
            total_calories += cal;
        }

        if (can && total_calories <= X) {
            l = m; // mは達成可能
        } else {
            r = m; // mは達成不可能
        }
    }

    cout << l << endl;
    return 0;
}