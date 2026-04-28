#include <iostream>
#include <stdio.h>
#include <algorithm>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 2e4 + 10;
const int M = 1e6 + 10;
int n, m;
int vis[N];

struct Pair { 
    int a, b, c;

    bool operator<(const Pair src)const {
        return c > src.c;
    }
};
namespace UnionFind {
    int father[N];

    int Find(int x) {
        if (father[x] == x) return x;
        return father[x] = Find(father[x]);
    }
}

Pair edge[M];
using namespace UnionFind;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> edge[i].a >> edge[i].b >> edge[i].c;
    sort(edge + 1, edge + m + 1);
    for (int i = 1; i <= n; i++) father[i] = i;
    for (int i = 1; i <= m; i++) {
        int a = Find(edge[i].a);
        int b = Find(edge[i].b);
        if (a == b) {
            printf("%d\n", edge[i].c);
            return 0;
        }
        if (!vis[a]) vis[a] = b;
        else father[Find(vis[a])] = b;
        if (!vis[b]) vis[b] = a;
        else father[Find(vis[b])] = a;
    }
    printf("0\n");
    return 0;
}