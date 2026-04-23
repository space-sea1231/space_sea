#include <iostream>
#include <stdio.h>
#include <queue>
#include <cstring>
#define __Debug
#define Change(x) x - 'A' + 1

using namespace std;
typedef long long ll;

const int N = 5e2 + 10;
const int M = 17;
const int K = 40;
const int INF = 0x3f3f3f3f;

int n, m, l;
char c[N][N];
int dis[M][M];
int vis[N][N];
int top;
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, 1, -1, 0};
int f[M][1 << M];
string g[M][1 << M];

struct Node {
    int x, y;
};
Node node[N];

void Dfs(Node root) {
    queue<Node> q;
    memset(vis, 0, sizeof(vis));
    q.push(root);
    vis[root.x][root.y] = 1;
    while (!q.empty()) {
        Node now = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int xx = now.x + dx[i];
            int yy = now.y + dy[i];
            if (xx < 1 || xx > n || yy < 1 || yy > m || c[xx][yy] == '*' || vis[xx][yy]) continue;
            vis[xx][yy] = vis[now.x][now.y] + 1;
            q.push((Node){xx, yy});
        }
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> l;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> c[i][j];
            if ('A' <= c[i][j] && c[i][j] <= 'Z') {
                node[Change(c[i][j])] = (Node){i, j};
            }
        }
    }
    for (int i = 1; i <= l; i++) {
        Dfs(node[i]);
        for (int j = 1; j <= l; j++) dis[i][j] = vis[node[j].x][node[j].y] - 1;
    }
    // for (int i = 1; i <= l; i++) {
    //     for (int j = 1; j <= l; j++) {
    //         printf("dis[%c][%c]=%d\n", c[node[i].x][node[i].y], c[node[j].x][node[j].y], dis[i][j]);
    //     }
    // }
    memset(f, 0x3f, sizeof(f));
    f[1][1] = 0;
    g[1][1] = "A";
    for (int k = 2; k <= (1 << l); k++) {
        for (int i = 1; i <= l; i++) {
            if ((k & (1 << (i - 1))) == false) continue;
            for (int j = 1; j <= l; j++) {
                if (i == j) continue;
                if ((k & (1 << (j - 1))) == false) continue;
                if (f[i][k] > f[j][k - (1 << (i - 1))] + dis[j][i]) {
                    f[i][k] = f[j][k - (1 << (i - 1))] + dis[j][i];
                    g[i][k] = g[j][k - (1 << (i - 1))] + (char)(i - 1 + 'A');
                }
                else if (f[i][k] == f[j][k - (1 << (i - 1))] + dis[j][i]
                && g[j][k - (1 << (i - 1))] + (char)(i - 1 + 'A') < g[i][k]) {
                    g[i][k] = g[j][k - (1 << (i - 1))] + (char)(i - 1 + 'A');
                }
            }
        }
    }
    int ans = INF;
    string s = " ";
    for (int i = 2; i <= l; i++) {
        if (ans > f[i][(1 << l) - 1]) {
            ans = f[i][(1 << l) - 1];
            s = g[i][(1 << l) - 1];
        }
        else if (ans == f[i][(1 << l) - 1] && s > g[i][(1 << l) - 1]) {
            s = g[i][(1 << l) - 1];
        }
    }
    printf("%d\n%s\n", ans, s.c_str());
    return 0;
}
/*
5 5 3
A.**C
*....
B*...
.**..
.....
*/