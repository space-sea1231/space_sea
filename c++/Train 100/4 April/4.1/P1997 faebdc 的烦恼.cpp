#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
const int M = 3e5 + 10;

int n, m;
int block;
int a[N];
int ans[M];

struct Node {
    int l, r;
    int pos;

    bool operator<(const Node src)const {
        if (l / block != src.l / block) return l < src.l;
        return ((l / block) & 1) ? r < src.r : r > src.r;
    }
};
Node node[M];

namespace Mos {
    int now;
    int cnt[M], bucket[N];

    void Add(int x) {
        bucket[cnt[x]]--;
        cnt[x]++;
        bucket[cnt[x]]++;
        now = max(now, cnt[x]);
        return;
    }
    void Delete(int x) {
        bucket[cnt[x]]--;
        cnt[x]--;
        bucket[cnt[x]]++;
        if (bucket[now] == 0) now--;
        return;
    }
} using namespace Mos;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    block = sqrt(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += N;
    }
    for (int i = 1; i <= m; i++) {
        cin >> node[i].l >> node[i].r;
        node[i].pos = i;
    }
    sort(node + 1, node + m + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        while (l > node[i].l) Add(a[--l]);
        while (r < node[i].r) Add(a[++r]);
        while (l < node[i].l) Delete(a[l++]);
        while (r > node[i].r) Delete(a[r--]);
        ans[node[i].pos] = now;
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}