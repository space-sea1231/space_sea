#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<int> adj(N, 0);
    for (int i = 0; i < M; i++) {
        int A, B;
        cin >> A >> B;
        --A; --B;
        adj[A] |= (1 << B);
        adj[B] |= (1 << A);
    }

    int SZ = 1 << N;

    // 预处理连通分量数
    vector<int> comp(SZ, 0);
    for (int mask = 1; mask < SZ; mask++) {
        int v = __builtin_ctz(mask);
        int visited = 0;
        queue<int> q;
        q.push(v);
        visited |= (1 << v);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            int nxt = adj[u] & mask & ~visited;
            while (nxt) {
                int w = __builtin_ctz(nxt);
                nxt &= nxt - 1;
                visited |= (1 << w);
                q.push(w);
            }
        }

        comp[mask] = 1 + comp[mask ^ visited];
    }

    // DP
    vector<int> f(SZ, 0);
    f[0] = 1;

    for (int mask = 1; mask < SZ; mask++) {
        long long res = 0;
        for (int T = mask; T; T = (T - 1) & mask) {
            if (comp[T] & 1) res += f[mask ^ T];
            else res -= f[mask ^ T];
        }
        f[mask] = (res % MOD + MOD) % MOD;
    }

    cout << f[SZ - 1] << '\n';
    return 0;
}