#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <bitset>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 2e5 + 10;

int n, m;
int block;
int a[N];
int ans[N];
bitset <N> bs;

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
    int cnt[N];

    void Add(int x) {
        cnt[x]++;
        if (cnt[x] == 1) bs.set(x, 0);
        return;
    }
    void Delete(int x) {
        cnt[x]--;
        if (cnt[x] == 0) bs.set(x, 1);
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
    bs.set();
    for (int i = 1; i <= m; i++) {
        while (l > node[i].l) Add(a[--l]);
        while (r < node[i].r) Add(a[++r]);
        while (l < node[i].l) Delete(a[l++]);
        while (r > node[i].r) Delete(a[r--]);
        ans[node[i].pos] = bs._Find_first();
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}