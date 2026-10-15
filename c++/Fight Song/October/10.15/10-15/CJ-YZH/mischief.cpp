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
const int N = 1e3 + 10;

int n, k0;
int a[N][N];
int pos[N * N];

struct Node {
    int sx, sy, fx, fy;
}; 
vector<Node> q;
void Px(int &x, int y, int px) {
    // printf("%d %d %d %d\n", x, y, px, y);
    q.emplace_back((Node){x, y, px, y});
    swap(pos[a[px][y]], pos[a[x][y]]); // [x][y] -> [px][y]
    swap(a[px][y], a[x][y]); // [x][y] -> [px][y]
    x = px;
}
void Py(int x, int &y, int py) {
    // printf("%d %d %d %d\n", x, y, x, py);
    q.emplace_back((Node){x, y, x, py});
    swap(pos[a[x][py]], pos[a[x][y]]); // [x][y] -> [x][py]
    swap(a[x][py], a[x][y]); // [x][y] -> [x][py]
    y = py;
}
signed main() {
    freopen("mischief.in", "r", stdin);
    freopen("mischief.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> k0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            pos[a[i][j]] = (i - 1) * n + j;
            // printf("pos[%d]=%d\n", a[i][j], (i - 1) * n + j);
        }
    }
    for (int i = 1; i <= n * n; i++) {
        int x = (pos[i] - 1) / n + 1, y = (pos[i] - 1) % n + 1;
        int px = (i - 1) / n + 1, py = (i - 1) % n + 1;
        if (x == px && y == py) continue;
        if (x == px) Py(x, y, py);
        else if (y == py) Px(x, y, px);
        else if (pos[a[px][y]] == a[px][y]) Py(x, y, py), Px(x, y, px);
        else Px(x, y, px), Py(x, y, py);
        // for (int ii = 1; ii <= n; ii++) {
        //     for (int jj = 1; jj <= n; jj++) {
        //         printf("%d ", a[ii][jj]);
        //     }
        //     printf("\n");
        // }
        // for (int ii = 1; ii <= n; ii++) {
        //     for (int jj = 1; jj <= n; jj++) {
        //         printf("pos[%d]=%d\n", a[ii][jj], (ii - 1) * n + jj);
        //     }
        // }
    }
    printf("%d\n", q.size());
    for (Node& cur : q) printf("%d %d %d %d\n", cur.sx, cur.sy, cur.fx, cur.fy);
    return 0;
}