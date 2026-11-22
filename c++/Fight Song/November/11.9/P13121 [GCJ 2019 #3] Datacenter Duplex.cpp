#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 110;
int T, n, m;
char c[N][N], ans[N][N];
int fa[N * N];

int id(int x, int y) { return (x - 1) * m + y; }

int Find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = Find(fa[x]);
}

void Dfs(int x, int y, int root) {
    fa[id(x, y)] = root;
    static int dx[4] = {-1, 0, 0, 1};
    static int dy[4] = {0, -1, 1, 0};
    for (int k = 0; k < 4; k++) {
        int xx = x + dx[k], yy = y + dy[k];
        if (xx < 1 || xx > n || yy < 1 || yy > m) continue;
        if (fa[id(xx, yy)] != 0) continue;
        if (c[xx][yy] != c[x][y]) continue;
        Dfs(xx, yy, root);
    }
}

void Solve(int cur) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> c[i][j];

    // 初始化并查集：每个格子自指
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            fa[id(i, j)] = id(i, j);

    // 先合并正交相邻的同色格子
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (i < n && c[i][j] == c[i + 1][j]) {
                int a = Find(id(i, j)), b = Find(id(i + 1, j));
                if (a != b) fa[a] = b;
            }
            if (j < m && c[i][j] == c[i][j + 1]) {
                int a = Find(id(i, j)), b = Find(id(i, j + 1));
                if (a != b) fa[a] = b;
            }
        }

    // 初始化输出为 '.'
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
            ans[i][j] = '.';

    // 贪心连对角：每个顶点最多一条，先尝试合并不同根的同色对角
    // 按行扫描，对每个 2x2 块
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            // '\' 连 (i,j)-(i+1,j+1)
            if (c[i][j] == c[i + 1][j + 1]) {
                int a = Find(id(i, j)), b = Find(id(i + 1, j + 1));
                if (a != b) {
                    fa[a] = b;
                    ans[i][j] = '\\';
                    continue;
                }
            }
            // '/' 连 (i+1,j)-(i,j+1)
            if (c[i + 1][j] == c[i][j + 1]) {
                int a = Find(id(i + 1, j)), b = Find(id(i, j + 1));
                if (a != b) {
                    fa[a] = b;
                    ans[i][j] = '/';
                    continue;
                }
            }
        }
    }

    // 检查 A 和 B 是否各自连通（各自恰好一个根）
    int rootA = -1, rootB = -1;
    bool ok = true;
    for (int i = 1; i <= n && ok; i++) {
        for (int j = 1; j <= m && ok; j++) {
            int r = Find(id(i, j));
            if (c[i][j] == 'A') {
                if (rootA == -1) rootA = r;
                else if (rootA != r) ok = false;
            } else {
                if (rootB == -1) rootB = r;
                else if (rootB != r) ok = false;
            }
        }
    }

    cout << "Case #" << cur << ": ";
    if (!ok) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    cout << "POSSIBLE\n";
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) cout << ans[i][j];
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    for (int i = 1; i <= T; i++) Solve(i);
    return 0;
}