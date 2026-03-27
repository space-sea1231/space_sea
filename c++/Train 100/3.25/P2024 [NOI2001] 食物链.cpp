#include <iostream>
#include <stdio.h>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 5e4 + 10;
int n, k;
int cnt;

namespace UnionFind {
    int fa[N << 2];

    int Find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = Find(fa[x]);
    }
}
using namespace UnionFind;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= n * 3; i++) fa[i] = i;
    for (int i = 1; i <= k; i++) {
        int opt, x, y;
        cin >> opt >> x >> y;
        if (x > n || y > n) {
            cnt++;
            #ifdef __Debug
            printf("Debug1:\n");
            #endif
            continue;
        }
        if (opt == 1) {
            if (Find(x) == Find(y + n) || Find(x + n) == Find(y)) {
                cnt++;
                #ifdef __Debug
                printf("Debug2: %d\n", i);
                #endif
                continue;
            }
            fa[Find(x)] = Find(y);
            fa[Find(x + n)] = Find(y + n);
            fa[Find(x + n * 2)] = Find(y + n * 2);
        }
        if (opt == 2) {
            if (Find(x) == Find(y) || Find(x) == Find(y + n) || x == y) {
                cnt++;
                #ifdef __Debug
                printf("Debug3:\n");
                #endif
                continue;
            }
            fa[Find(x)] = Find(y + n * 2);
            fa[Find(x + n)] = Find(y);
            fa[Find(x + n * 2)] = Find(y + n);
        }
    }
    printf("%d\n", cnt);
    return 0;
}