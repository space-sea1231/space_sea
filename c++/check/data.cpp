#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
typedef long long ll;

mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());
inline int Random(int l, int r) {return Rand() % (r - l + 1) + l;}
const int INF = sizeof(int) == 4 ? 1e9 + 1 : 1e18 + 1;

bool vis[11][11];

signed main() {
    srand((unsigned)time(0));

    int n = Random(1, 5);
    int m = Random(1, 5);
    int W = Random(1, n * n);
    printf("%d %d\n%d\n", n, m, W);
    for (int i = 1; i <= W; i++) {
        int x = Random(0, n);
        int y = Random(0, m);
        while(vis[x][y]) {
            x = Random(0, n);
            y = Random(0, m);
        }
        vis[x][y] = true;
        printf("%d %d\n", x, y);
    }
    int k = Random(1, 3);
    printf("%d\n", k);
    return 0;
}