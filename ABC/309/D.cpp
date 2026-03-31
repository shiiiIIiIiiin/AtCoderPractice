#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int dist(int start,vector<vector<int>> &G,vector<bool> &visited) {
	vector<int> cnt(visited.size(),0);
	queue<pair<int,int>> q;
	q.push({ start,0 });
	visited[start] = true;
	cnt[start] = 0;

	while (!q.empty()) {
		int pos = q.front().first,dis=q.front().second;

		q.pop();
		for (int i = 0; i < G[pos].size(); i++) {
			int nex = G[pos][i];
			if (visited[nex])continue;
			q.push({ nex,dis + 1 });
			cnt[nex] = dis + 1;
			visited[nex] = true;
		}
	}
	

	int M = -1;
	for (int i = 1; i < cnt.size(); i++)M = max(M, cnt[i]);

	return M;
}

int main() {
	int N1, N2, M; cin >> N1 >> N2 >> M;
	int N = N1 + N2;
	vector<vector<int>> G(N + 1);

	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}

	//頂点１から一番遠い点と頂点Nから一番遠い点をつなぐ
	//BFSで探索する

	vector<int> d1(N1+1, 0), d2(N2+1, 0);
	vector<bool> visited(N + 1,false);
	cout << dist(1, G, visited) + dist(N, G, visited) + 1;
	
}