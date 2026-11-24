#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 3e3 + 10;
const int M = 1e3 + 10;
const int K = 2e2 + 10;
const int Mod = 998244353;

// int g[N][M], f[N][M];
int pt[M];

struct Node {
    int l, r;

    bool operator<(const Node &s) const {
        if (l == s.l) return r < s.r;
        return l < s.l;
    }
}; Node node[N];

int Add(int x, int y) { return (ll)x + y >= Mod ? x + y - Mod : x + y; }
void init(int c, int t) {}
vector<int> segment(int n, int m, int k, vector<int> l, vector<int> r) {
    for (int i = 0; i < n; i++) node[i] = (Node){l[i], r[i]};
    sort(node, node + n);
    for (int i = 1; i <= m; i++) pt[i] = n;
    for (int i = 0; i <= m; i++) {
        for (int j = i ? pt[i - 1] : 0; j < n; j++) {
            if (node[j].l > i) {
                pt[i] = j;
                break;
            }
        }
    }
    vector<vector<int> > f(m + 1, vector<int>(n));
    vector<vector<int> > g(m + 1, vector<int>(n));
    vector<int> ans(k + 1); ans[1] = n;
    fill(g[0].begin(), g[0].end(), 1);
    for (int s = 2; s <= k; s++) {
        for (int i = 0; i <= m; i++) fill(f[i].begin(), f[i].end(), 0);
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j < n; j++) {
                if (!g[i][j]) continue;
                auto [minn, maxn] = minmax(node[j].r, i);
                int l = max(pt[minn], j + 1), r = pt[maxn] - 1;
                if (l <= r) {
                    f[maxn][l] = Add(f[maxn][l], g[i][j]);
                    f[maxn][r + 1] = Add(f[maxn][r + 1], Mod - g[i][j]);
                }
            }
        }
        for (int i = 0; i <= m; i++) {
            for (int j = 0, sum = 0; j < n; j++) {
                sum = Add(sum, f[i][j]);
                g[i][j] = sum;
                ans[s] = Add(ans[s], sum);
            }
        }
    }
    return ans;
}
/*
Light snow wispers that the year is folding up.
小雪轻声说，一年正在合上书页。
*/