#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 3e3 + 10;

int n, m;
int num, maxn;
int a[N];
int belong[N], siz[N];
int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};
char c[4] = {'W', 'N', 'E', 'S'};
vector<int> e[N];

inline int Change(int x, int y) {return (x - 1) * 51 + y;}
inline bool Check(int x, int y) {return x >= 1 && x <= n && y >= 1 && y <= m;}

void Bfs(int root) {
    queue<int> q;
    q.push(root);
    belong[root] = ++num;
    siz[num] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v:e[u]) {
            if (belong[v]) continue;
            belong[v] = num;
            siz[num]++;
            q.push(v);
        }
    }
    maxn = max(maxn, siz[num]);
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int id = Change(i, j);
            cin >> a[id];
            int tmp = 15 - a[id];
            for (int k = 3; ~k; k--) {
                if (tmp & (1 << k)) {
                    tmp ^= (1 << k);
                    int x = i + dx[k];
                    int y = j + dy[k];
                    // if (id == 15) printf("Debug:%d %d\n", x, y);
                    if (Check(x, y)) {
                        // cerr<<id << " " << Change(x, y) << endl;
                        // cerr<<id << " " << x<< " " << y << endl;
                        e[Change(i, j)].emplace_back(Change(x, y));
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!belong[Change(i, j)]) {
                Bfs(Change(i, j));
            }
        }
    }
    int ans = 0, p1, p2;
    for (int j = m; j; j--) {
        for (int i = 1; i <= n; i++) {
            int id = Change(i, j);
            for (int k = 2; k >= 1; k--) {
                if (a[id] & (1 << k)) {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (Check(x, y) && belong[id] != belong[Change(x, y)]) {
                        int val = siz[belong[id]] + siz[belong[Change(x, y)]];
                        if (ans <= val) {
                            ans = val;
                            p1 = id, p2 = k;
                        }
                    }
                }
            }
        }
    }
    printf("%d\n%d\n%d\n%d %d %c", num, maxn, ans, p1 / 51 + 1, (p1 - 1) % 51 + 1, c[p2]);
    return 0;
}