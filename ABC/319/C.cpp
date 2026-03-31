//#define _GLIBCXX_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <unordered_map>
#include <stack>
#include <string>
#include <cmath>
#include <iomanip>
#include <deque>
#include <unordered_set>
#include <locale>
#include <random>

using namespace std;
using ll = long long;

const ll MOD = 998244353;
const ll MOD2 = 1'000'000'007;

long long modinv(long long a, long long m) {
    long long b = m, u = 1, v = 0;
    while (b) {
        long long t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= m; if (u < 0) u += m;
    return u;
}

long long modpow(long long a, long long n, long long mod) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

int dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };

const ll INF = LLONG_MAX / 2;

//cin.tie(nullptr);
//ios::sync_with_stdio(false);

int N = 3;

bool check(vector<vector<int>>& G, vector<pair<int, int>>& P) {
    vector<vector<bool>> visited(N, vector<bool>(N, false));


    for (int i = 0; i < N * N; i++) {
        auto [x, y] = P[i];
        visited[x][y] = true;

        if (x == y) {//右下斜め
            if (visited[0][0] && visited[1][1] && visited[2][2]) {
                set<int> st;
                for (int k = 0; k < 3; k++)st.insert(k);
                st.erase(x);

                vector<int> memo;
                for (auto x : st)memo.push_back(x);

                if (G[memo[0]][memo[0]] == G[memo[1]][memo[1]])return false;

            }
        }

        if (x + y == 2) {//左下斜め
            if (visited[0][2] && visited[1][1] && visited[2][0]) {
                set<pair<int, int>> st;
                for (int k = 0; k < N; k++)st.insert({ k,2 - k });

                st.erase({ x,y });

                vector<pair<int, int>> memo;
                for (auto p : st)memo.push_back(p);

                if (G[memo[0].first][memo[0].second] == G[memo[1].first][memo[1].second])return false;
            }
        }

        if (visited[x][0] && visited[x][1] && visited[x][2]) {
            vector<int> memo;
            for (int k = 0; k < N; k++)if (k != y)memo.push_back(k);
            if (G[x][memo[0]] == G[x][memo[1]])return false;
        }

        if (visited[0][y] && visited[1][y] && visited[2][y]) {
            vector<int> memo;
            for (int k = 0; k < N; k++)if (k != x)memo.push_back(k);
            if (G[memo[0]][y] == G[memo[1]][y])return false;
        }


    }

    return true;
}


int main() {
    //全ての順番を試せばいい
    vector<vector<int>> G(N, vector<int>(N));

    for (int i = 0; i < N; i++)for (int j = 0; j < N; j++)cin >> G[i][j];

    vector<pair<int,int>> P;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)P.push_back({ i,j });
    }

    ll cnt = 0;

    do {
        //Pの順番で空けていくシミュレーションをする
        if (check(G, P))cnt++;
    } while (next_permutation(P.begin(), P.end()));

    ll a = 1;
    for (ll i = 1; i <= 9; i++)a *= i;
    double ans = (double)cnt / a;

    cout << fixed << setprecision(10) << ans << endl;
}