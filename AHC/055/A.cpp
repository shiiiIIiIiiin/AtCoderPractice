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
#include <chrono>

using namespace std;
using ll = long long;

vector<ll> H_orig, C_orig;
vector<vector<ll>> A;
ll N;

int cal_score(const vector<int>& P);
void print_ans(const vector<int>& P);
bool check_weak(int w, int b);


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    auto start_time = chrono::steady_clock::now();

    cin >> N;
    H_orig.resize(N);
    C_orig.resize(N);
    A.assign(N, vector<ll>(N));

    for (int i = 0; i < N; i++) cin >> H_orig[i];
    for (int i = 0; i < N; i++) cin >> C_orig[i];
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> A[i][j];


    // --- ここから開ける宝箱の順番Pの初期値を決める (トポロジカルソート版) ---
    vector<vector<int>> graph(N);
    vector<int> in_degree(N, 0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            // 武器iで宝箱jを倒せるなら、i -> j の辺を張る
            if (check_weak(i, j)) {
                graph[i].push_back(j);
                in_degree[j]++;
            }
        }
    }

    queue<int> q;
    for (int i = 0; i < N; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> dp(N, 1);
    vector<int> parent(N, -1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : graph[u]) {
            if (dp[v] < dp[u] + 1) {
                dp[v] = dp[u] + 1;
                parent[v] = u;
            }
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    int max_path_len = 0;
    int path_end_node = -1;
    for (int i = 0; i < N; i++) {
        if (dp[i] > max_path_len) {
            max_path_len = dp[i];
            path_end_node = i;
        }
    }

    vector<int> P;
    vector<bool> in_path(N, false);
    if (path_end_node != -1) {
        int curr = path_end_node;
        while (curr != -1) {
            P.push_back(curr);
            in_path[curr] = true;
            curr = parent[curr];
        }
        reverse(P.begin(), P.end());
    }

    vector<pair<ll, int>> remaining_chests;
    for (int i = 0; i < N; i++) {
        if (!in_path[i]) {
            remaining_chests.push_back({H_orig[i], i});
        }
    }
    sort(remaining_chests.begin(), remaining_chests.end());

    for (const auto& pair : remaining_chests) {
        P.push_back(pair.second);
    }
    // --- 順番の初期値決めここまで ---


    vector<int> ans = P;
    int cur_score = cal_score(ans);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, N - 1);
    
    while (true) {
        auto current_time = chrono::steady_clock::now();
        double elapsed_time = chrono::duration_cast<chrono::milliseconds>(current_time - start_time).count();
        if (elapsed_time > 1940.0) break;

        int i = distrib(gen);
        int j = distrib(gen);
        if (i == j) continue;

        swap(ans[i], ans[j]);
        int s = cal_score(ans);
        if (s < cur_score) {
            cur_score = s;
        } else {
            swap(ans[i], ans[j]);
        }
    }

    print_ans(ans);
}


int cal_score(const vector<int>& P_const) {
    vector<int> P = P_const;
    vector<ll> H = H_orig;
    vector<ll> C = C_orig;
    vector<priority_queue<pair<ll, int>>> pq(N);
    int cnt_T = 0;

    for (auto i : P) {
        while (!pq[i].empty()) {
            auto [x, idx] = pq[i].top(); pq[i].pop();
             if (C[idx] <= 0) continue;
            ll needed_attacks = (H[i] > 0 && x > 0) ? (H[i] + x - 1) / x : 0;
            ll attack_count = min(C[idx], needed_attacks);
            C[idx] -= attack_count;
            cnt_T += attack_count;
            H[i] -= x * attack_count;
            if (H[i] <= 0) break;
        }
        if (H[i] > 0) cnt_T += H[i];
        for (int j = 0; j < N; j++) pq[j].push({ A[i][j], i });
    }
    return cnt_T;
}

void print_ans(const vector<int>& P_const) {
    vector<int> P = P_const;
    vector<ll> H = H_orig;
    vector<ll> C = C_orig;
    vector<priority_queue<pair<ll, int>>> pq(N);

    for (auto i : P) {
        while (!pq[i].empty()) {
            auto [x, idx] = pq[i].top(); pq[i].pop();
            if (C[idx] <= 0) continue;
            while (C[idx] > 0 && H[i] > 0) {
                C[idx]--;
                cout << idx << " " << i << endl;
                H[i] -= x;
            }
            if (H[i] <= 0) break;
        }
        if (H[i] > 0) {
            for (int j = 0; j < H[i]; j++) cout << -1 << " " << i << endl;
        }
        for (int j = 0; j < N; j++) pq[j].push({ A[i][j], i });
    }
}

bool check_weak(int w, int b) {
    return A[w][b] * max((ll)C_orig[w], 2LL) >= H_orig[b];
}