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

signed main() {
    srand((unsigned)time(0));
    int T = 1;
    printf("%d\n", T);
    while (T--) {
        int n = Random(2, 5);
        int m = Random(2, 5);
        printf("%d %d\n", n, m);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int flag = Random(0, 1);
                printf("%c", flag ? 'T' : '#');
            }
            printf("\n");
        }
    }
    return 0;
}