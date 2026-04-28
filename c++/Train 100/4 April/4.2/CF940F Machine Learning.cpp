#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <bitset>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int n, m;
int block;
int a[N];
int ans[N];
int tmp[N << 1];
int cntn, cnto;
bitset <N> bs;

struct Node {
    int l, r;
    int pos, t;

    bool operator<(const Node src)const {
        if (l / block != src.l / block) return l < src.l;
        if (r / block != src.r / block) return r < src.r;
        return t < src.t;
    }
};
Node node[N];

struct Operation {
    int x, y;
};
Operation opt[N];

namespace Mos {
    int cnt[N];
    int bucket[N];

    void Add(int x) {
        bucket[cnt[x]]--;
        if (bucket[cnt[x]] == 0) bs.set(cnt[x], 1);
        cnt[x]++;
        bucket[cnt[x]]++;
        if (bucket[cnt[x]] == 1) bs.set(cnt[x], 0);
        return;
    }
    void Delete(int x) {
        bucket[cnt[x]]--;
        if (bucket[cnt[x]] == 0) bs.set(cnt[x], 1);
        cnt[x]--;
        bucket[cnt[x]]++;
        if (bucket[cnt[x]] == 1) bs.set(cnt[x], 0);
        return;
    }
} using namespace Mos;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    block = pow(n, 2.0 / 3.0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        tmp[i] = a[i];
    }
    for (int i = 1; i <= m; i++) {
        int x, l, r;
        cin >> x >> l >> r;
        if (x == 1) node[++cntn] = (Node){l, r, cntn, cnto};
        if (x == 2) {
            opt[++cnto] = (Operation){l, r};
            tmp[cnto + n] = r;
        }
    }
    sort(tmp + 1, tmp + n + cnto + 1);
    int len = unique(tmp + 1, tmp + n + cnto + 1) - tmp - 1;
    for (int i = 1; i <= n; i++) a[i] = lower_bound(tmp + 1, tmp + len + 1, a[i]) - tmp;
    for (int i = 1; i <= cnto; i++) opt[i].y = lower_bound(tmp + 1, tmp + len + 1, opt[i].y) - tmp;
    sort(node + 1, node + cntn + 1);
    int l = 1, r = 0, last = 0;
    bs.set(), bs.set(0, 0);
    for (int i = 1; i <= cntn; i++) {
        while (l > node[i].l) Add(a[--l]);
        while (r < node[i].r) Add(a[++r]);
        while (l < node[i].l) Delete(a[l++]);
        while (r > node[i].r) Delete(a[r--]);
        while (last < node[i].t) {
            last++;
            if (node[i].l <= opt[last].x && opt[last].x <= node[i].r) {
                Add(opt[last].y);
                Delete(a[opt[last].x]);
            }
            swap(opt[last].y, a[opt[last].x]);
        }
        while (last > node[i].t) {
            if (node[i].l <= opt[last].x && opt[last].x <= node[i].r) {
                Add(opt[last].y);
                Delete(a[opt[last].x]);
            }
            swap(opt[last].y, a[opt[last].x]);
            last--;
        }
        ans[node[i].pos] = bs._Find_first();
    }
    for (int i = 1; i <= cntn; i++) printf("%d\n", ans[i]);
    return 0;
}