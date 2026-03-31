#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
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

ll dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };
const ll INF = LLONG_MAX / 2;

//cin.tie(nullptr);
//ios::sync_with_stdio(false);

void dfs(set<int>& st, vector<bool>& ans, int pos, int pre, bool up, vector<int>& A, vector<vector<int>>& G) {
    
    for (int i = 0; i < G[pos].size(); i++) {
        int nex = G[pos][i];
        if (nex == pre)continue;

        if (up) {
            ans[nex] = true;
            dfs(st, ans, nex, pos, up, A, G);
        }
        else if (st.count(A[nex])) {//こいつ以下全部答えはYes
            up = true;
            ans[nex] = true;
            dfs(st, ans, nex, pos, up, A, G);
            up = false;
        }
        else {
            st.insert(A[nex]);
            dfs(st, ans, nex, pos, up, A, G);
            st.erase(A[nex]);
        }
    }
}

int main() {
    int N; cin >> N;
    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++)cin >> A[i];
    vector<vector<int>> G(N + 1);

    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    //木をdfsする、それまでのやつが含まれてたらそれより下は全部No

    vector<bool> ans(N + 1, false);
    set<int> st;//1から自分までのパスの間に含まれるすべての数字
    st.insert(A[1]);
    dfs(st, ans, 1, -1, false, A, G);

    for (int i = 1; i <= N; i++)cout << (ans[i] ? "Yes" : "No") << endl;
}

