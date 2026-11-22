#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n = 0) { init(n); }
    void init(int n) {
        p.resize(n);
        r.assign(n, 0);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) ++r[a];
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    for (int tc = 1; tc <= T; ++tc) {
        int C;
        cin >> C;
        int M = 2 * C;
        vector<int> L(M + 1), A(M + 1);
        vector<vector<int>> in(C + 1), out(C + 1);
        long long sumD = 0;
        for (int i = 1; i <= M; ++i) {
            int e, l, d;
            cin >> e >> l >> d;
            L[i] = l;
            A[i] = (l + d) % 24;
            sumD += d;
            int u = (i - 1) / 2 + 1;
            out[u].push_back(i);
            in[e].push_back(i);
        }
        auto wait = [&](int p, int q) -> int {
            int w = (L[q] - A[p]) % 24;
            if (w < 0) w += 24;
            return w;
        };

        vector<int> minCost(C + 1, 0), opt(C + 1, 0), extra(C + 1, 0);
        for (int v = 2; v <= C; ++v) {
            int p0 = in[v][0], p1 = in[v][1];
            int q0 = out[v][0], q1 = out[v][1];
            int c0 = wait(p0, q0) + wait(p1, q1);
            int c1 = wait(p0, q1) + wait(p1, q0);
            if (c1 < c0) {
                minCost[v] = c1; opt[v] = 1; extra[v] = c0 - c1;
            } else {
                minCost[v] = c0; opt[v] = 0; extra[v] = c1 - c0;
            }
        }

        const long long INF64 = (1LL << 60);
        long long best = INF64;
        vector<int> succ(M + 1), comp(M + 1);

        for (int s : out[1]) {
            for (int d : in[1]) {
                int d_other = in[1][0] == d ? in[1][1] : in[1][0];
                int s_other = out[1][0] == s ? out[1][1] : out[1][0];

                long long sumPair = wait(d, s) + wait(d_other, s_other);
                succ[d] = s;
                succ[d_other] = s_other;
                for (int v = 2; v <= C; ++v) {
                    sumPair += minCost[v];
                    int p0 = in[v][0], p1 = in[v][1];
                    int q0 = out[v][0], q1 = out[v][1];
                    if (opt[v] == 0) {
                        succ[p0] = q0; succ[p1] = q1;
                    } else {
                        succ[p0] = q1; succ[p1] = q0;
                    }
                }

                fill(comp.begin(), comp.end(), -1);
                int k = 0;
                for (int i = 1; i <= M; ++i) if (comp[i] == -1) {
                    int cur = i;
                    while (comp[cur] == -1) {
                        comp[cur] = k;
                        cur = succ[cur];
                    }
                    ++k;
                }

                long long mst = 0;
                bool ok = true;
                if (k > 1) {
                    struct E2 {int u, v, w;};
                    vector<E2> es;
                    for (int v = 2; v <= C; ++v) {
                        int c0 = comp[in[v][0]];
                        int c1 = comp[in[v][1]];
                        if (c0 != c1) es.push_back({c0, c1, extra[v]});
                    }
                    sort(es.begin(), es.end(),
                         [](const E2& a, const E2& b){ return a.w < b.w; });
                    DSU dsu(k);
                    int taken = 0;
                    for (auto &e : es) {
                        if (dsu.unite(e.u, e.v)) {
                            mst += e.w;
                            if (++taken == k - 1) break;
                        }
                    }
                    if (taken != k - 1) ok = false;
                }
                if (!ok) continue;

                long long totalWait = sumPair + mst - wait(d, s) + L[s];
                long long total = sumD + totalWait;
                best = min(best, total);
            }
        }
        cout << "Case #" << tc << ": " << best << "\n";
    }
    return 0;
}