#include<iostream>
#include<vector>
#include<queue>
#include<climits>
using namespace std;
using ll = long long;

int main() {
	int A, B, C; cin >> A >> B >> C;

	if (abs(A) == abs(B)) {
		if (A == B||C%2==0) {
			cout << "=";
			return 0;
		}
		else {
			cout << (A < B ? "<" : ">");
			return 0;
		}
		
	}
	else if (A >= 0 && B >= 0) {
		cout << (A < B ? "<" : ">");
		return 0;
	}
	else {
		if (A < B && C % 2 == 1) {
			cout << "<";
			return 0;
		}
		else if (B < A && C % 2 == 1) {
			cout << ">";
		}
		else {
			cout << (abs(A) < abs(B) ? "<" : ">");
			return 0;
		}
	}
}