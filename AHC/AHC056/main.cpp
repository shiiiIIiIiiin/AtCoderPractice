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
#include <tuple> 

using namespace std;


int dr[] = { -1, 1, 0, 0, 0 }; // U, D, L, R, S
int dc[] = { 0, 0, -1, 1, 0 };
char dir_char[] = { 'U', 'D', 'L', 'R', 'S' };
int opposite_dir[] = { 1, 0, 3, 2, 4 };

bool can_move(int r, int c, int dir, int N, const std::vector<std::string>& v, const std::vector<std::string>& h) {
    if (dir == 0) return r > 0 && h[r - 1][c] == '0';
    if (dir == 1) return r < N - 1 && h[r][c] == '0';
    if (dir == 2) return c > 0 && v[r][c - 1] == '0';
    if (dir == 3) return c < N - 1 && v[r][c] == '0';
    return false;
}

// 経路復元 (map<pair, pair> 版)
vector<pair<int, int>> reconstruct_path(
    const map<pair<int, int>, pair<int, int>>& parent,
    pair<int, int> start, pair<int, int> end
) {
    vector<pair<int, int>> path;
    pair<int, int> curr = end;
    while (curr.first != -1) {
        path.push_back(curr);
        if (curr == start) break;
        if (parent.find(curr) == parent.end()) break;
        curr = parent.at(curr);
    }
    reverse(path.begin(), path.end());
    return path;
}

// 1. 通常のBFS (最短経路)
pair<int, map<pair<int, int>, pair<int, int>>> runBFS(
    int N, pair<int, int> start, pair<int, int> end,
    const vector<string>& v, const vector<string>& h
) {
    queue<pair<int, int>> q;
    q.push(start);
    map<pair<int, int>, pair<int, int>> parent;
    vector<vector<int>> dist(N, vector<int>(N, -1));
    dist[start.first][start.second] = 0;
    parent[start] = { -1, -1 };
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (r == end.first && c == end.second) break;
        for (int dir = 0; dir < 4; dir++) {
            if (can_move(r, c, dir, N, v, h)) {
                int nr = r + dr[dir];
                int nc = c + dc[dir];
                if (dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    parent[{nr, nc}] = { r, c };
                    q.push({ nr, nc });
                }
            }
        }
    }
    return { dist[end.first][end.second], parent };
}


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N, K, T; cin >> N >> K >> T;

    vector<string> v(N);
    vector<string> h(N - 1);

    for (int i = 0; i < N; i++) cin >> v[i];
    for (int i = 0; i < N - 1; i++) cin >> h[i];

    vector<pair<int, int>> target(K);
    for (int i = 0; i < K; i++) cin >> target[i].first >> target[i].second;

    // --- Phase 0: C*Q=T 戦略 (オフライン計算) ---

    // 0a. 全経路 (full_path) と移動 (D_map) を計算
    // ★バグ修正: full_path と D_map の生成ロジックを修正

    vector<pair<int, int>> full_path; // t=0..X の座標リスト (サイズ X+1)
    full_path.push_back(target[0]);

    vector<int> D_map; // t=0..X-1 の移動方向リスト (サイズ X)

    long long X = 0; // 最短総ステップ数
    bool reachable_bfs = true;

    for (int k = 0; k < K - 1; k++) {
        pair<int, int> start = target[k];
        pair<int, int> end = target[k + 1];
        auto [steps, parent] = runBFS(N, start, end, v, h);

        if (steps == -1) { // 到達不能
            reachable_bfs = false;
            break;
        }

        X += steps;
        auto path = reconstruct_path(parent, start, end);

        // path は [start, p1, p2, ..., end]
        for (size_t i = 0; i < path.size() - 1; ++i) {
            pair<int, int> p1 = path[i];
            pair<int, int> p2 = path[i + 1];

            // D_map (t=0..X-1)
            int dir_idx = 0; // U
            if (p2.first - p1.first == 1) dir_idx = 1; // D
            else if (p2.second - p1.second == -1) dir_idx = 2; // L
            else if (p2.second - p1.second == 1) dir_idx = 3; // R
            D_map.push_back(dir_idx);

            // full_path (t=1..X)
            full_path.push_back(p2);
        }
    }
    // ★バグ修正ここまで (full_path.size() == X+1, D_map.size() == X が保証される)


    if (reachable_bfs == false || X > T) {
        // (V<K になる)
        cout << 1 << " " << 1 << " " << 0 << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) cout << 0 << (j == N - 1 ? "" : " ");
            cout << endl;
        }
        return 0;
    }

    // 0b. 「次に訪れるt」を計算 (t_next_visit)
    map<pair<int, int>, vector<int>> visits_at_coord;
    for (int t = 0; t <= X; ++t) {
        visits_at_coord[full_path[t]].push_back(t);
    }

    vector<int> t_next_visit(X + 1); // t_next_visit[t] = tの次にそのマスを訪れるステップ
    for (int t = 0; t <= X; ++t) {
        pair<int, int> coord = full_path[t];
        auto& visits = visits_at_coord[coord];
        // visits (ソート済み) の中で t を二分探索
        auto it = lower_bound(visits.begin(), visits.end(), t);
        if (it != visits.end() && next(it) != visits.end()) {
            t_next_visit[t] = *next(it); // 次の訪問ステップ
        }
        else {
            t_next_visit[t] = -1; // これが最後の訪問
        }
    }

    // --- Phase 1: C, Q, M を計算 ---
    int C_base = ceil(sqrt(X + 1));
    int Q = ceil((double)(X + 1) / C_base);
    int C = C_base; // +1 は「もう使わないマス」用の色 (C_unused)
    int C_unused = 0;

    int M = X + 1; // t=0..X の (X+1) 個のルール

    // --- Phase 3: 遷移規則 ---
    // Build simple signatures per t and group them; then apply a frequency-weighted greedy merge
    // to reduce the number of representative groups L, and set C~=sqrt(L), Q~=sqrt(L).

    // build signature id per t
    struct Sig { int r,c,d,nd; };
    auto make_key = [&](int r,int c,int d,int nd)->long long {
        return ((long long)r<<48) ^ ((long long)c<<32) ^ ((long long)d<<16) ^ (long long)(nd+128);
    };
    unordered_map<long long,int> sig_map;
    vector<int> t_to_sig(X+1,-1);
    vector<long long> sig_keys;
    int next_sig = 0;
    int cap_delta = 10;
    for (int t = 0; t <= X; ++t) {
        auto p = full_path[t];
        int d = (t < (int)D_map.size()) ? D_map[t] : 4;
        int nd = (t_next_visit[t] == -1) ? -1 : min(cap_delta, t_next_visit[t]-t);
        long long k = make_key(p.first, p.second, d, nd);
        auto it = sig_map.find(k);
        if (it == sig_map.end()) {
            sig_map[k] = next_sig++;
            sig_keys.push_back(k);
            t_to_sig[t] = next_sig-1;
        } else t_to_sig[t] = it->second;
    }
    int L = max(1, next_sig);

    // rep t and freq
    vector<int> rep_t(L, -1), freq(L,0);
    for (int t = 0; t <= X; ++t) {
        int s = t_to_sig[t];
        if (rep_t[s] == -1) rep_t[s] = t;
        freq[s]++;
    }

    // basic group struct
    struct Group { int gid; int rep_t; int r,c; int d; int nd; int freq; bool alive; };
    vector<Group> groups;
    groups.reserve(L*2+10);
    for (int s = 0; s < L; ++s) {
        int t = rep_t[s];
        int r=0,cpos=0,d=4,nd=-1;
        if (t>=0) { r = full_path[t].first; cpos = full_path[t].second; d = (t<(int)D_map.size())?D_map[t]:4; nd = (t_next_visit[t]==-1)?-1:min(cap_delta,t_next_visit[t]-t); }
        groups.push_back({s, rep_t[s], r, cpos, d, nd, freq[s], true});
    }

    // target reduced L
    int curL = L;
    int targetL = max(1, L/3);

    // helper cost
    auto cost_between = [&](int a,int b)->double{
        Group &A = groups[a]; Group &B = groups[b];
        double posd = abs(A.r - B.r) + abs(A.c - B.c);
        double ddir = (A.d==B.d)?0.0:1.0;
        double dnd = (A.nd==B.nd)?0.0: (double)abs(A.nd - B.nd)/ (cap_delta+1);
        double base = 0.5*posd + 1.0*ddir + 0.2*dnd;
        double freqnorm = max(1, A.freq + B.freq);
        return base / freqnorm;
    };

    // spatial buckets
    unordered_map<long long, vector<int>> buckets;
    auto pos_key = [&](int r,int c){ return ((long long)r<<32) ^ (unsigned long long)c; };
    for (int i = 0; i < (int)groups.size(); ++i) if (groups[i].alive) buckets[pos_key(groups[i].r, groups[i].c)].push_back(i);

    // candidate pq
    using Item = tuple<double,int,int>;
    struct Cmp { bool operator()(Item const&a, Item const&b) const { return get<0>(a) > get<0>(b); } };
    priority_queue<Item, vector<Item>, Cmp> pq;

    int L_allpairs_thresh = 1000;
    if (L <= L_allpairs_thresh) {
        for (int i = 0; i < L; ++i) for (int j = i+1; j < L; ++j) pq.emplace(cost_between(i,j), i, j);
    } else {
        int R = 3;
        for (int i = 0; i < L; ++i) if (groups[i].alive) {
            for (int drd=-R; drd<=R; ++drd) for (int dcd=-R; dcd<=R; ++dcd) {
                long long k = pos_key(groups[i].r+drd, groups[i].c+dcd);
                auto it = buckets.find(k); if (it==buckets.end()) continue;
                for (int j : it->second) if (j>i) pq.emplace(cost_between(i,j), i, j);
            }
        }
    }

    // mapping of sig->current group id
    vector<int> curGroup(L);
    for (int s = 0; s < L; ++s) curGroup[s] = s;

    // merge loop (naive updates)
    while (curL > targetL && !pq.empty()) {
        auto [cst, ga, gb] = pq.top(); pq.pop();
        // find current representative group ids
        int ra = -1, rb = -1;
        if (ga < (int)groups.size()) ra = ga; else continue;
        if (gb < (int)groups.size()) rb = gb; else continue;
        if (!groups[ra].alive || !groups[rb].alive) continue;
        if (ra == rb) continue;
        // merge ra and rb
        Group A = groups[ra], B = groups[rb];
        Group G;
        G.gid = groups.size();
        G.rep_t = (A.freq >= B.freq) ? A.rep_t : B.rep_t;
        int totf = A.freq + B.freq;
        G.r = (A.r*A.freq + B.r*B.freq)/max(1, totf);
        G.c = (A.c*A.freq + B.c*B.freq)/max(1, totf);
        G.d = (A.freq >= B.freq) ? A.d : B.d;
        G.nd = (A.nd>=0?A.nd:0) + (B.nd>=0?B.nd:0);
        G.freq = totf;
        G.alive = true;
        // mark old dead
        groups[ra].alive = false; groups[rb].alive = false;
        groups.push_back(G);
        int newgid = G.gid;
        // update curGroup for all signatures: map old groups to newgid
        for (int s = 0; s < L; ++s) {
            if (curGroup[s] == ra || curGroup[s] == rb) curGroup[s] = newgid;
        }
        // add to buckets
        buckets[pos_key(G.r,G.c)].push_back(newgid);
        // push neighbor candidates
        int R2 = 3;
        for (int drd=-R2; drd<=R2; ++drd) for (int dcd=-R2; dcd<=R2; ++dcd) {
            long long k = pos_key(G.r+drd, G.c+dcd);
            auto it = buckets.find(k); if (it==buckets.end()) continue;
            for (int j : it->second) if (j!=newgid && groups[j].alive) {
                double cc = cost_between(j,newgid);
                pq.emplace(cc, j, newgid);
            }
        }
        curL--;
    }

    // build merged index mapping
    unordered_map<int,int> mergedIdx;
    int mcnt = 0;
    for (int i = 0; i < (int)groups.size(); ++i) if (groups[i].alive) mergedIdx[i] = mcnt++;
    int Lp = max(1, mcnt);

    // rep t per merged
    vector<int> rep_merged(Lp, -1);
    for (int s = 0; s < L; ++s) {
        int gid = curGroup[s];
        if (mergedIdx.find(gid) == mergedIdx.end()) continue;
        int mid = mergedIdx[gid];
        if (rep_merged[mid] == -1) rep_merged[mid] = rep_t[s];
    }

    int C2 = max(1, (int)floor(sqrt((double)Lp)));
    int Q2 = (Lp + C2 - 1) / C2;
    int Cout = C2 + 1;
    int C_unused2 = C2;

    cout << Cout << " " << Q2 << " " << (Q2 * Cout) << endl;

    // --- build initial_board for output (recreate but do not print earlier) ---
    vector<vector<int>> initial_board(N, vector<int>(N, C_unused));
    map<pair<int, int>, bool> has_been_set2;
    for (int t = 0; t <= X; ++t) {
        pair<int,int> pos = full_path[t];
        if (!has_been_set2[pos]) {
            initial_board[pos.first][pos.second] = t % C_base;
            has_been_set2[pos] = true;
        }
    }
    vector<vector<int>> board_out = initial_board;
    for (int s = 0; s < L; ++s) {
        int t = rep_t[s]; if (t < 0) continue;
        int gid = curGroup[s]; if (mergedIdx.find(gid) == mergedIdx.end()) continue;
        int mid = mergedIdx[gid]; auto p = full_path[t]; board_out[p.first][p.second] = mid % C2;
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) cout << board_out[i][j] << (j==N-1?"":" ");
        cout << endl;
    }

    // output rules: for each merged index => representative t
    vector<int> rep_final = rep_merged;
    for (int q = 0; q < Q2; ++q) {
        for (int c = 0; c < Cout; ++c) {
            if (c == C_unused2) {
                // unused color column: stop/idle rule
                cout << c << " " << q << " " << C_unused2 << " " << q << " " << dir_char[4] << endl;
                continue;
            }
            int idx = q * C2 + c;
            if (idx >= Lp) { cout << c << " " << q << " " << C_unused2 << " " << q << " " << dir_char[4] << endl; continue; }
            int t = rep_final[idx];
            if (t < 0) { cout << c << " " << q << " " << C_unused2 << " " << q << " " << dir_char[4] << endl; continue; }
            int A,Snew,D;
            if (t == X) { A = C_unused2; Snew = q; D = 4; }
            else {
                int nxt = t_next_visit[t];
                if (nxt == -1) A = C_unused2;
                else {
                    int s_next = t_to_sig[nxt]; int gid = curGroup[s_next]; int mid = (mergedIdx.find(gid)==mergedIdx.end())?0:mergedIdx[gid]; A = mid % C2;
                }
                int s_next = (t_next_visit[t]==-1)?-1:t_to_sig[t_next_visit[t]];
                if (s_next == -1) Snew = q;
                else { int gid = curGroup[s_next]; int mid = (mergedIdx.find(gid)==mergedIdx.end())?0:mergedIdx[gid]; Snew = mid / C2; }
                D = (t < (int)D_map.size()) ? D_map[t] : 4;
            }

            // SAFETY: ensure the move D is legal on the given map; if not, make it a Stop
            auto can_move_char = [&](int rr,int cc,char Dc)->bool{
                if (Dc=='S') return true;
                if (Dc=='U') return rr>0 && h[rr-1][cc]=='0';
                if (Dc=='D') return rr<N-1 && h[rr][cc]=='0';
                if (Dc=='L') return cc>0 && v[rr][cc-1]=='0';
                if (Dc=='R') return cc<N-1 && v[rr][cc]=='0';
                return false;
            };
            // coordinate of this representative
            int rr = full_path[t].first, cc = full_path[t].second;
            char Dch2 = dir_char[D];
            if (!can_move_char(rr,cc,Dch2)) {
                // invalid move: replace with stop
                D = 4; Dch2 = dir_char[D];
                A = C_unused2;
                Snew = q;
            }
            // clamp Snew
            if (Snew < 0) Snew = 0;
            if (Snew >= Q2) Snew = Q2-1;
            cout << c << " " << q << " " << A << " " << Snew << " " << dir_char[D] << endl;
        }
    }

    return 0;
}