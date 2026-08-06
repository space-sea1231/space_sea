#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e3 + 10;
const int M = 3e2 + 10;

int n, m, v, e;
int c[N], d[N];
int edge[M][M];
double k[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    memset(edge, 0x3f, sizeof(edge));
    cin >> n >> m >> v >> e;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i <= n; i++) cin >> d[i];
    for (int i = 1; i <= n; i++) cin >> k[i];
    for (int i = 1; i <= n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        edge[x][y] = edge[y][x] = min(edge[x][y], z);
    }
    return 0;
}