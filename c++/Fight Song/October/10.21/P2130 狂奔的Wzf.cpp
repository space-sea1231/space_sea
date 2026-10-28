#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e3 + 10;
const int K = 11;

int n, m;
bool a[N][N];
int rol[N][N], cur[N][N];
int dis[N][N];
bool vis[N][N];
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

bool Check(int x, int y, int xx, int yy) { 
    if (1 <= xx && xx <= n && 1 <= yy && yy <= m) {
        if (x > xx) swap(x, xx);
        if (y > yy) swap(y, yy);
        if (x == xx) return !(rol[x][yy] - rol[x][y - 1]);
        if (y == yy) return !(cur[xx][y] - cur[x - 1][y]);
    }
    return false;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    int fx, fy;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            if (c == 'X') a[i][j] = true;
            if (c == '#') fx = i, fy = j; 
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            rol[i][j] = rol[i][j - 1] + a[i][j];
        }
    }
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            cur[i][j] = cur[i - 1][j] + a[i][j];
        }
    }
    queue<pair<int, int> > q;
    q.push(make_pair(1, 1));
    vis[1][1] = true;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        if (x == fx && y == fy) { printf("%d\n", dis[x][y]); return 0; }
        for (int i = 0; i < 4; i++) {
            for (int k = 0; k < K; k++) {
                int xx = x + dx[i] * (1 << k);
                int yy = y + dy[i] * (1 << k);
                if (!Check(x, y, xx, yy)) { k = K; continue; }
                if (!vis[xx][yy]) {
                    vis[xx][yy] = true;
                    dis[xx][yy] = dis[x][y] + 1;
                    q.push(make_pair(xx, yy));
                } 
            }
        }
    }
    printf("-1\n");
    return 0;
}