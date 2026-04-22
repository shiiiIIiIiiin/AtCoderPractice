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

void check(string& s) {
    if (s.size() < 4)return;

    int n = s.size();

    if (s[n - 4] == '(' && s[n - 3] == 'x' && s[n - 2] == 'x' && s[n - 1] == ')') {
        for (int i = 0; i < 4; i++)s.pop_back();
        s += "xx";
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int T; cin >> T;

    for (; T--;) {
        //グリッドを白黒で塗った時の数で、絶対にいけないケースがある（（１，１）を黒としたとき、黒（１，１）→・・・→黒（N,N）となるので、黒の数は白の数より1多くないとだめ）
        //よって、Nが奇数の時絶対無理


        int N, A, B; cin >> N >> A >> B;
        A--; B--;

        if (N % 2 == 1) {
            cout << "No" << endl;
            continue;
        }

        if ((A + B) % 2 == 0) {//いけないマスが黒
            cout << "No" << endl;
            continue;
        }

        //iPadの通りの動きをさせる

        string ans = "";

        for (int h = 0; h < A - 1; h++) {
            if (h % 2 == 0)for (int i = 0; i < N - 1; i++)ans += 'R';
            else for (int i = 0; i < N - 1; i++)ans += 'L';
            ans += 'D';
        }

        if (A % 2 == 0) {
            if (A != 0) {
                for (int i = 0; i < (N - B) / 2; i++)ans += "DLUL";
                ans += 'L';
                for (int i = 0; i < B / 2; i++)ans += "DLUL";
                ans += "DD";

                for (int h = A + 1; h < N; h++) {
                    if (h % 2 == 0)for (int i = 0; i < N - 1; i++)ans += 'L';
                    else for (int i = 0; i < N - 1; i++)ans += 'R';
                    ans+='D';
                }
            }
            else {
                for (int i = 0; i < B / 2; i++)ans += "DRUR";
                ans += "DR";
                for (int i = 0; i < (N - B) / 2; i++)ans += "RURD";
                ans += "D";

                for (int h = 2; h < N; h++) {
                    if (h % 2 == 0) for (int i = 0; i < N - 1; i++) ans += 'L';
                    else for (int i = 0; i < N - 1; i++) ans += 'R';
                    ans += 'D';
                }
            }
        }
        else {
            for (int i = 0; i < B / 2; i++)ans += "DRUR";
            ans += "RD";
            for (int i = 0; i < (N - B - 2) / 2; i++)ans += "RURD";
            ans += "D";

            for (int h = A + 1; h < N; h++) {
                if (h % 2 == 0)for (int i = 0; i < N - 1; i++)ans += 'L';
                else for (int i = 0; i < N - 1; i++)ans += 'R';
                ans += 'D';
            }


        }

        cout << "Yes" << endl;
        int x = 0, y = 0;
        for (auto c : ans) {
            cout << c;
            if (c == 'L')y--;
            if (c == 'R')y++;
            if (c == 'U')x--;
            if (c == 'D')x++;

            if (x == N - 1 && y == N - 1) {
                cout << endl;
                break;
            }
        }

        cout << endl;
    }
}