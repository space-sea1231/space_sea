#include <iostream>
#include <stdio.h>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 3e4 + 10;
int t;
namespace UnionFind {
    int fa[N], dist[N], size[N];

    int Find(int x) {
        if (x == fa[x]) return x;
        int father = Find(fa[x]);
        dist[x] += dist[fa[x]];
        return fa[x] = father;
    }
    void Merge(int x, int y) {//2 = 1, 3 = 2
        x = Find(x), y = Find(y);
        dist[x] = size[y];
        fa[x] = y;
        size[y] += size[x];
        return;
    }
    int Query(int x, int y) {
        #ifdef __Debug
        printf("query-0:%d %d\n", x, y);
        #endif
        int fx = Find(x), fy = Find(y);
        #ifdef __Debug
        printf("query-1:%d %d\n", x, y);
        #endif
        if (fx != fy) return -1;
        return abs(dist[x] - dist[y]) - 1;
    }
}
using namespace UnionFind;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> t;
    for (int i = 1; i < N; i++) {
        fa[i] = i;
        size[i] = 1;
    }
    for (int i = 1; i <= t; i++) {
        char opt;
        int x, y;
        cin >> opt >> x >> y;
        if (opt == 'M') Merge(x, y);
        if (opt == 'C') printf("%d\n",Query(x, y));
    }
    #ifdef __Debug
    for (int i = 1; i <= t; i++) printf("dist[%d] = %d\n", i, dist[i]);
    #endif
    return 0;
}