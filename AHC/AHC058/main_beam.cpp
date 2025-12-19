#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, L, T, K;

struct State
{
    ll score;
    vector<vector<ll>> P, B;
    vector<pair<int, int>> actions;

    State() {}
    State(int _score) : score(_score), P(L, vector<ll>(N, 0)), B(L, vector<ll>(N, 1)) {}
};

// 状態を1ターン進める
State advance(const State &s, int lv, int j, const vector<ll> &A, const vector<vector<ll>> &C)
{
    State ns = s;

    // 購入
    if (lv != -1)
    {
        ll cost = C[lv][j] * (ns.P[lv][j] + 1);
        ns.score -= cost;
        ns.P[lv][j]++;
        ns.actions.push_back({lv, j});
    }
    else
    {
        ns.actions.push_back({-1, -1});
    }

    // 生産
    for (int i = 0; i < L; i++)
    {
        if (i == 0)
        {
            for (int k = 0; k < N; k++)
                ns.score += A[k] * ns.B[i][k] * ns.P[i][k];
        }
        else
        {
            for (int k = 0; k < N; k++)
                ns.B[i - 1][k] += ns.B[i][k] * ns.P[i][k];
        }
    }

    return ns;
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

    const int BEAM_WIDTH = 50; // ビーム幅

    vector<State> beam;
    beam.push_back(State(K));

    for (int turn = 0; turn < T; turn++)
    {
        vector<State> next_beam;

        for (const auto &state : beam)
        {
            // 生産のみ
            next_beam.push_back(advance(state, -1, -1, A, C));

            // 各レベル・各機械を購入
            for (int lv = L - 1; lv >= 0; lv--)
            {
                for (int j = 0; j < N; j++)
                {
                    ll cost = C[lv][j] * (state.P[lv][j] + 1);
                    if (cost <= state.score)
                    {
                        next_beam.push_back(advance(state, lv, j, A, C));
                    }
                }
            }
        }

        // スコアでソートして上位BEAM_WIDTH個を残す
        sort(next_beam.begin(), next_beam.end(), [](const State &a, const State &b)
             { return a.score > b.score; });

        if (next_beam.size() > BEAM_WIDTH)
        {
            next_beam.resize(BEAM_WIDTH);
        }

        beam = next_beam;
    }

    // 最良の結果を出力
    const State &best = beam[0];
    for (int t = 0; t < T; t++)
    {
        if (best.actions[t].first == -1)
            cout << -1 << '\n';
        else
            cout << best.actions[t].first << ' ' << best.actions[t].second << '\n';
    }

    return 0;
}
