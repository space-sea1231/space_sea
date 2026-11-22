#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug

using namespace std;
typedef long long ll;

const ll INF = 1e17 + 1; 
const int N = 5e2 + 10;
const int M = 5e5 + 10;

int c, n, m, d, Q;
ll dist[N][N];
int a[M];

vector<pair<int, int> > e[M];
int read() {
    char c = getchar();
    int flag = 1;
    while (c < '0' || c > '9') {
        if (c == '-') flag = -1;
        c = getchar();
    }
    int sum = 0;
    while ('0' <= c && c <= '9') {
        sum = (sum << 1) + (sum << 3) + (c ^ 48);
        c = getchar();
    }
    return sum * flag;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    // ll cnt = 0;
    // for (int i = 1; i <= 500; i++) {
    //     for (int j = 1; j <= 500; j++) {
    //         for (int k = 1; k <= 500; k++) {
    //             if (i < j + k) cnt = i;
    //         }
    //     }
    // }
    c = read(), n = read(), m = read(), d = read(), Q = read();
    for (int i = 1; i <= m; i++) a[i] = read();
    for (int i = 1; i <= n; i++) {
        int k;
        k = read();
        for (int j = 1; j <= k; j++) {
            int a, t;
            a = read(), t = read();
            e[a].emplace_back(make_pair(i, t));
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = INF;
        }
        dist[i][i] = 0;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 0, lim = e[i].size(); j < lim; j++) {
            for (int k = j + 1; k < lim; k++) {
                int u = e[i][j].first, v = e[i][k].first;
                dist[u][v] = dist[v][u] = min(dist[u][v], (ll)e[i][j].second + e[i][k].second);
            }
        }
    }
    // int st = clock();
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (i == k) continue;
            for (int j = 1; j <= n; j++) {
                if (i == j || j == k) continue;
                if (dist[i][j] > dist[i][k] + dist[k][j]) dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    // int ed = clock();
    while (Q--) {
        int x, y;
        ll ans = INF;
        x = read(), y = read();
        for (int i = 0, limi = e[x].size(); i < limi; i++) {
            for (int j = 0, limj = e[y].size(); j < limj; j++) {
                ans = min(ans, e[x][i].second + dist[e[x][i].first][e[y][j].first] + e[y][j].second);
            }
        }
        printf("%lld\n", a[x] + a[y] + ans);
    }
    // cerr<<(double)(ed - st) / 1000000<< "\n";
    return 0;
}