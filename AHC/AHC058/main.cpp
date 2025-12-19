#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = LLONG_MAX / 2;

int N, L, T, K;

// 与えられた閾値でシミュレーション、最終スコアを返す
ll simulate_strategy(int phase1_end, int phase2_end, int phase3_end, const vector<ll> &A, const vector<vector<ll>> &C, vector<pair<int, int>> &out_pts)
{
    out_pts.assign(T, {-1, -1});
    ll score = K;
    vector<vector<ll>> P(L, vector<ll>(N, 0)), B(L, vector<ll>(N, 1));
    int idx = 0;

    // Phase 1: strengthen level 0
    while (idx < phase1_end && idx < T)
    {
        int lv = 0;
        int best_j = -1;
        double best_eff = -1.0;
        for (int j = 0; j < N; j++)
        {
            ll cost = C[lv][j] * (P[lv][j] + 1);
            if (cost > score)
                continue;
            double eff = (double)A[j] * B[lv][j] / (double)cost;
            if (eff > best_eff)
            {
                best_eff = eff;
                best_j = j;
            }
        }
        if (best_j != -1)
        {
            ll cost = C[lv][best_j] * (P[lv][best_j] + 1);
            out_pts[idx] = {lv, best_j};
            score -= cost;
            P[lv][best_j]++;
        }
        for (int i = 0; i < L; i++)
        {
            if (i == 0)
            {
                for (int j = 0; j < N; j++)
                    score += A[j] * B[i][j] * P[i][j];
            }
            else
            {
                for (int j = 0; j < N; j++)
                    B[i - 1][j] += B[i][j] * P[i][j];
            }
        }
        idx++;
    }

    // Phase 2: strengthen level 1-3 (prioritize higher level: 3 > 2 > 1)
    while (idx < phase2_end && idx < phase3_end && idx < T)
    {
        int best_i = -1, best_j = -1;

        // レベル3で購入可能な機械を探す
        int best_j_lv3 = -1;
        double best_eff_lv3 = -1.0;
        for (int j = 0; j < N; j++)
        {
            ll cost = C[3][j] * (P[3][j] + 1);
            if (cost > score)
                continue;
            double eff = (double)A[j] * B[3][j] / (double)cost;
            if (eff > best_eff_lv3)
            {
                best_eff_lv3 = eff;
                best_j_lv3 = j;
            }
        }

        // レベル2で購入可能な機械を探す
        int best_j_lv2 = -1;
        double best_eff_lv2 = -1.0;
        for (int j = 0; j < N; j++)
        {
            ll cost = C[2][j] * (P[2][j] + 1);
            if (cost > score)
                continue;
            double eff = (double)A[j] * B[2][j] / (double)cost;
            if (eff > best_eff_lv2)
            {
                best_eff_lv2 = eff;
                best_j_lv2 = j;
            }
        }

        // レベル1で購入可能な機械を探す
        int best_j_lv1 = -1;
        double best_eff_lv1 = -1.0;
        for (int j = 0; j < N; j++)
        {
            ll cost = C[1][j] * (P[1][j] + 1);
            if (cost > score)
                continue;
            double eff = (double)A[j] * B[1][j] / (double)cost;
            if (eff > best_eff_lv1)
            {
                best_eff_lv1 = eff;
                best_j_lv1 = j;
            }
        }

        // レベルの高い順に優先：3 > 2 > 1
        if (best_j_lv3 != -1)
        {
            best_i = 3;
            best_j = best_j_lv3;
        }
        else if (best_j_lv2 != -1)
        {
            best_i = 2;
            best_j = best_j_lv2;
        }
        else if (best_j_lv1 != -1)
        {
            best_i = 1;
            best_j = best_j_lv1;
        }
        if (best_i != -1)
        {
            ll cost = C[best_i][best_j] * (P[best_i][best_j] + 1);
            out_pts[idx] = {best_i, best_j};
            score -= cost;
            P[best_i][best_j]++;
        }
        for (int i = 0; i < L; i++)
        {
            if (i == 0)
            {
                for (int j = 0; j < N; j++)
                    score += A[j] * B[i][j] * P[i][j];
            }
            else
            {
                for (int j = 0; j < N; j++)
                    B[i - 1][j] += B[i][j] * P[i][j];
            }
        }
        idx++;
    }

    // Phase 3: strengthen level 2-3 (prioritize higher level: 3 > 2)
    while (idx < phase3_end && idx < T)
    {
        int best_i = -1, best_j = -1;

        // レベル3で購入可能な機械を探す
        int best_j_lv3 = -1;
        double best_eff_lv3 = -1.0;
        for (int j = 0; j < N; j++)
        {
            ll cost = C[3][j] * (P[3][j] + 1);
            if (cost > score)
                continue;
            double eff = (double)A[j] * B[3][j] / (double)cost;
            if (eff > best_eff_lv3)
            {
                best_eff_lv3 = eff;
                best_j_lv3 = j;
            }
        }

        // レベル2で購入可能な機械を探す
        int best_j_lv2 = -1;
        double best_eff_lv2 = -1.0;
        for (int j = 0; j < N; j++)
        {
            ll cost = C[2][j] * (P[2][j] + 1);
            if (cost > score)
                continue;
            double eff = (double)A[j] * B[2][j] / (double)cost;
            if (eff > best_eff_lv2)
            {
                best_eff_lv2 = eff;
                best_j_lv2 = j;
            }
        }

        // レベル3が購入可能なら優先
        if (best_j_lv3 != -1)
        {
            best_i = 3;
            best_j = best_j_lv3;
        }
        else if (best_j_lv2 != -1)
        {
            best_i = 2;
            best_j = best_j_lv2;
        }

        if (best_i != -1)
        {
            ll cost = C[best_i][best_j] * (P[best_i][best_j] + 1);
            out_pts[idx] = {best_i, best_j};
            score -= cost;
            P[best_i][best_j]++;
        }
        for (int i = 0; i < L; i++)
        {
            if (i == 0)
            {
                for (int j = 0; j < N; j++)
                    score += A[j] * B[i][j] * P[i][j];
            }
            else
            {
                for (int j = 0; j < N; j++)
                    B[i - 1][j] += B[i][j] * P[i][j];
            }
        }
        idx++;
    }

    // 残りのターンは生産のみ
    while (idx < T)
    {
        out_pts[idx] = {-1, -1};
        for (int i = 0; i < L; i++)
        {
            if (i == 0)
            {
                for (int j = 0; j < N; j++)
                    score += A[j] * B[i][j] * P[i][j];
            }
            else
            {
                for (int j = 0; j < N; j++)
                    B[i - 1][j] += B[i][j] * P[i][j];
            }
        }
        idx++;
    }
    return score;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> L >> T >> K;
    vector<ll> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];
    vector<vector<ll>> C(L, vector<ll>(N));
    for (int i = 0; i < L; i++)
        for (int j = 0; j < N; j++)
            cin >> C[i][j];

    // ランダムシード初期化（時刻ベース）
    srand((unsigned)time(nullptr));

    vector<pair<int, int>> best_pts(T, {-1, -1});
    ll best_score = -INF;

    // 初期解：固定フェーズ定義 を使用
    vector<pair<int, int>> pts_initial;
    ll score_initial = simulate_strategy(100, 200, T - 50, A, C, pts_initial);
    best_pts = pts_initial;
    best_score = score_initial;

    // 時間がある限りランダムに閾値を試す
    auto start_time = chrono::high_resolution_clock::now();
    int iteration_count = 0;
    while (true)
    {
        auto now = chrono::high_resolution_clock::now();
        auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(now - start_time).count();
        if (elapsed_ms > 1900) // 1.9秒で停止
            break;

        // phase1_end, phase2_end, phase3_end をランダムに生成
        int max_phase3_end = T;
        int phase3_end = max(100, rand() % max_phase3_end); // 最後は生産のみ、最低100ターンは購入可能
        int max_phase2_end = phase3_end;
        int phase2_end = rand() % (max_phase2_end + 1);
        int phase1_end = rand() % (phase2_end + 1);

        vector<pair<int, int>> pts;
        ll score = simulate_strategy(phase1_end, phase2_end, phase3_end, A, C, pts);

        if (score > best_score)
        {
            best_score = score;
            best_pts = pts;
        }

        iteration_count++;
    }

    // 最良戦略を出力
    for (int t = 0; t < T; t++)
    {
        if (best_pts[t].first == -1)
            cout << -1 << '\n';
        else
            cout << best_pts[t].first << ' ' << best_pts[t].second << '\n';
    }
    return 0;
}
