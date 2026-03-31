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

const ll MOD = 998244353;
const ll MOD2 = 1'000'000'007;

class UnionFind {
public:
    vector<ll> siz, par;
    UnionFind(ll n) {
        siz.assign(n, 1);
        par.assign(n, -1);
    }
    ll root(ll x) {
        return par[x] == -1 ? x : par[x] = root(par[x]);
    }
    void unite(ll x, ll y) {
        ll rx = root(x), ry = root(y);
        if (rx == ry) return;
        if (siz[rx] < siz[ry]) {
            par[rx] = ry;
            siz[ry] += siz[rx];
        }
        else {
            par[ry] = rx;
            siz[rx] += siz[ry];
        }
    }
    bool same(ll x, ll y) {
        return root(x) == root(y);
    }
};

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

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int N, T, M, K;
    long long L;
    if (!(cin >> N >> T >> M >> K >> L)) return 0;
    vector<int> x(N), y(N), vx(N), vy(N);
    for (int i = 0; i < N; ++i) cin >> x[i] >> y[i] >> vx[i] >> vy[i];

    // K-means-like clustering on torus for initial grouping
    const double PI = acos(-1.0);
    auto torus_dx = [&](double a, double b)->double {
        double d = fabs(a - b);
        return min(d, (double)L - d);
    };
    auto torus_dist2 = [&](int i, double cx, double cy)->double {
        double dxv = torus_dx(x[i], cx);
        double dyv = torus_dx(y[i], cy);
        return dxv*dxv + dyv*dyv;
    };

    // Convert to double centers
    vector<double> cx(M), cy(M);
    vector<int> assign(N, -1);
    // kmeans++ initialization
    std::mt19937 rng(123456);
    uniform_int_distribution<int> uni(0, N-1);
    int first = uni(rng);
    cx[0] = x[first]; cy[0] = y[first];
    for (int k = 1; k < M; ++k) {
        // compute min dist^2 to existing centroids
        vector<double> d2(N);
        double sum = 0;
        for (int i = 0; i < N; ++i) {
            double best = 1e300;
            for (int j = 0; j < k; ++j) {
                double ddx = torus_dx(x[i], cx[j]);
                double ddy = torus_dx(y[i], cy[j]);
                double val = ddx*ddx + ddy*ddy;
                if (val < best) best = val;
            }
            d2[i] = best;
            sum += d2[i];
        }
        if (sum == 0) {
            int pick = uni(rng);
            cx[k] = x[pick]; cy[k] = y[pick];
            continue;
        }
        double r = std::uniform_real_distribution<double>(0, sum)(rng);
        double acc = 0;
        int pick = 0;
        for (int i = 0; i < N; ++i) {
            acc += d2[i];
            if (acc >= r) { pick = i; break; }
        }
        cx[k] = x[pick]; cy[k] = y[pick];
    }

    // iterate k-means on torus (treat x and y as angles separately)
    // run for a time budget so we can use more execution time to improve centers
    using clock = std::chrono::steady_clock;
    auto time_start = clock::now();
    const int total_budget_ms = 1800; // total allowed ms for expensive phases (can adjust)
    const int km_budget_ms = (int)(total_budget_ms * 0.6); // allocate 60% to k-means
    int iter = 0;
    while (iter < 10000) {
        auto now = clock::now();
        int elapsed = (int)std::chrono::duration_cast<std::chrono::milliseconds>(now - time_start).count();
        if (elapsed >= km_budget_ms) break;
        // assignment
        for (int i = 0; i < N; ++i) {
            double best = 1e300; int bid = 0;
            for (int j = 0; j < M; ++j) {
                double ddx = torus_dx(x[i], cx[j]);
                double ddy = torus_dx(y[i], cy[j]);
                double val = ddx*ddx + ddy*ddy;
                if (val < best) { best = val; bid = j; }
            }
            assign[i] = bid;
        }
        // update centroids with circular mean
    for (int j = 0; j < M; ++j) {
            double sum_cos_x = 0, sum_sin_x = 0, sum_cos_y = 0, sum_sin_y = 0;
            int cnt = 0;
            for (int i = 0; i < N; ++i) if (assign[i] == j) {
                double angx = (2.0*PI*x[i]) / L;
                sum_cos_x += cos(angx);
                sum_sin_x += sin(angx);
                double angy = (2.0*PI*y[i]) / L;
                sum_cos_y += cos(angy);
                sum_sin_y += sin(angy);
                ++cnt;
            }
            if (cnt == 0) {
                // reinit to a random point
                int p = uni(rng);
                cx[j] = x[p]; cy[j] = y[p];
            } else {
                double mean_ang_x = atan2(sum_sin_x, sum_cos_x);
                if (mean_ang_x < 0) mean_ang_x += 2.0*PI;
                double mean_ang_y = atan2(sum_sin_y, sum_cos_y);
                if (mean_ang_y < 0) mean_ang_y += 2.0*PI;
                cx[j] = mean_ang_x * L / (2.0*PI);
                cy[j] = mean_ang_y * L / (2.0*PI);
            }
        }
        ++iter;
    }

    // collect clusters
    vector<vector<int>> clusters(M);
    for (int i = 0; i < N; ++i) clusters[assign[i]].push_back(i);

    // balance clusters to have exactly K each
    // build list of surplus and deficit clusters
    vector<int> surplus_idx, deficit_idx;
    for (int j = 0; j < M; ++j) {
        if ((int)clusters[j].size() > K) surplus_idx.push_back(j);
        else if ((int)clusters[j].size() < K) deficit_idx.push_back(j);
    }
    // precompute distances to centroid for surplus clusters and sort descending
    for (int s : surplus_idx) {
        auto &v = clusters[s];
        sort(v.begin(), v.end(), [&](int a, int b){
            return torus_dist2(a, cx[s], cy[s]) > torus_dist2(b, cx[s], cy[s]);
        });
    }
    // move points from surplus to deficits: move farthest points to nearest deficit by centroid distance
    for (int s : surplus_idx) {
        while ((int)clusters[s].size() > K) {
            // choose farthest point
            int move_pt = clusters[s].back(); clusters[s].pop_back();
            // find deficit cluster closest to this point's position
            int bestd = -1; double bestdist = 1e300;
            for (int d : deficit_idx) {
                if ((int)clusters[d].size() >= K) continue;
                double dd = torus_dist2(move_pt, cx[d], cy[d]);
                if (dd < bestdist) { bestdist = dd; bestd = d; }
            }
            if (bestd == -1) {
                // fallback: put into first deficit
                for (int d : deficit_idx) { if ((int)clusters[d].size() < K) { bestd = d; break; } }
            }
            if (bestd != -1) clusters[bestd].push_back(move_pt);
        }
    }
    // If still mismatched (shouldn't happen), flatten and repartition
    bool need_repartition = false;
    for (int j = 0; j < M; ++j) if ((int)clusters[j].size() != K) need_repartition = true;
    vector<int> final_order;
    if (need_repartition) {
        final_order.reserve(N);
        for (int j = 0; j < M; ++j) for (int id : clusters[j]) final_order.push_back(id);
        // fill groups by taking K sequentially
        clusters.assign(M, {});
        for (int i = 0; i < N; ++i) clusters[i / K].push_back(final_order[i]);
    }

    // Output merges: for each cluster, output edges of its minimum spanning tree (Kruskal)
    int merges_needed = N - M;
    int printed = 0;
    for (int g = 0; g < M && printed < merges_needed; ++g) {
        int sz = (int)clusters[g].size();
        if (sz <= 1) continue;
        // build edges between local indices
        struct Edge { long long w; int u, v; };
        vector<Edge> edges;
        edges.reserve((size_t)sz * (sz-1) / 2);
        for (int i = 0; i < sz; ++i) for (int j = i+1; j < sz; ++j) {
            int gi = clusters[g][i];
            int gj = clusters[g][j];
            long long dx = llabs((long long)x[gi] - (long long)x[gj]);
            long long dy = llabs((long long)y[gi] - (long long)y[gj]);
            dx = min(dx, L - dx);
            dy = min(dy, L - dy);
            double dist = sqrt((double)dx * (double)dx + (double)dy * (double)dy);
            long long D = llround(dist);
            edges.push_back({D, i, j});
        }
        sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b){ return a.w < b.w; });
        // kruskal to pick initial tree edges
        UnionFind uf(sz);
        int taken = 0;
        vector<Edge> tree_edges;
        tree_edges.reserve(sz-1);
        for (auto &e : edges) {
            if (uf.same(e.u, e.v)) continue;
            uf.unite(e.u, e.v);
            tree_edges.push_back(e);
            ++taken;
            if (taken == sz - 1) break;
        }

        // local improvement: try to replace a tree edge with a non-tree edge that
        // connects two components when that tree edge removed, if it shortens total length
        // limited budget per cluster
        int improve_iters = 300; // small budget
        while (improve_iters-- > 0) {
            bool improved = false;
            for (size_t ei = 0; ei < tree_edges.size() && !improved; ++ei) {
                // remove tree_edges[ei], build UF of remaining tree edges
                UnionFind uf2(sz);
                for (size_t ej = 0; ej < tree_edges.size(); ++ej) if (ej != ei) {
                    uf2.unite(tree_edges[ej].u, tree_edges[ej].v);
                }
                // try any non-tree edge that connects the two components created
                for (auto &cand : edges) {
                    // skip if cand already in tree
                    bool in_tree = false;
                    for (auto &te : tree_edges) if (te.u==cand.u && te.v==cand.v) { in_tree = true; break; }
                    if (in_tree) continue;
                    if (!uf2.same(cand.u, cand.v)) {
                        // valid replacement: compute current tree length and new length
                        long long cur_len = 0;
                        for (auto &te : tree_edges) cur_len += te.w;
                        long long new_len = cur_len - tree_edges[ei].w + cand.w;
                        if (new_len < cur_len) {
                            tree_edges[ei] = cand;
                            improved = true;
                            break;
                        }
                    }
                }
            }
            if (!improved) break;
        }

        // output tree edges
        for (auto &e : tree_edges) {
            int gi = clusters[g][e.u];
            int gj = clusters[g][e.v];
            cout << 0 << ' ' << gi << ' ' << gj << '\n';
            ++printed;
            if (printed >= merges_needed) break;
        }
    }

    return 0;
}