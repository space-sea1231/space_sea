#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 2e5 + 10;
const int M = 1e6 + 10;

int n, m;
int block;
int a[N];
ll ans[N];

struct Node {
    int l, r;
    int pos;

    bool operator<(const Node src)const {
        if (l / block != src.l / block) return l < src.l;
        return ((l / block) & 1) ? r < src.r : r > src.r;
    }
};
Node node[N];

namespace Mos {
    ll now;
    int cnt[M];

    void Add(int x) {
        now -= (ll)cnt[x] * cnt[x] * x;
        cnt[x]++;
        now += (ll)cnt[x] * cnt[x] * x;
        #ifdef __Debug
        printf("Debug: x=%d now=%d\n", x, now);
        #endif
        return;
    }
    void Delete(int x) {
        now -= (ll)cnt[x] * cnt[x] * x;
        cnt[x]--;
        now += (ll)cnt[x] * cnt[x] * x;
        return;
    }
} using namespace Mos;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    block = sqrt(n);
    for (int i = 1; i <= n; i++) cin >> a[i];
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
        #ifdef __Debug
        printf("Debug2: %d\n", ans[node[i].pos]);
        #endif
    }
    for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
    return 0;
}