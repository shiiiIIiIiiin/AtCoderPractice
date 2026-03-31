#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<algorithm>
#include<map>
#include<set>
using namespace std;
using ll = long long;

int main() {
	string D; cin >> D;
	
	for (int i = 0; i < D.size(); i++) {
		if (D[i] == 'N')D[i] = 'S';
		else if (D[i] == 'E')D[i] = 'W';
		else if (D[i] == 'W')D[i] = 'E';
		else if (D[i] == 'S')D[i] = 'N';
	}

	cout << D;

}