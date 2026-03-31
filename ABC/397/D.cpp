#include <iostream>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;
using ll = cpp_int;

ll integer_sqrt(ll n) {
    ll left = 0, right = n, ans = 0;
    while (left <= right) {
        ll mid = (left + right) / 2;
        if (mid * mid <= n) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}

int main() {
    ll N;
    cin >> N;
    vector<pair<ll, ll>> bunkai;

    for (ll i = 1; i * i * i <= N; i++) {
        if (N % i == 0) bunkai.emplace_back(i, N / i);
    }

    for (auto [a, b] : bunkai) {
        ll D = 9 * a * a - 12 * (a * a - b);
        if (D < 0) continue;

        ll sqrtD = integer_sqrt(D);
        if (sqrtD * sqrtD != D) continue;

        ll memo_num = -3 * a + sqrtD;
        if (memo_num % 6 != 0) continue;

        ll y = memo_num / 6;
        if (y <= 0) continue;

        if (3 * y * y + 3 * a * y + a * a - b == 0) {
            cout << a + y << " " << y << endl;
            return 0;
        }
    }

    cout << -1 << endl;
}