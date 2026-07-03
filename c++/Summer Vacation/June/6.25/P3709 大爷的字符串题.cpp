#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 2e5 + 10;

int n, m;
int a[N], tmp[N];
int bucket[N], cnt[N];
int ans[N];
int block;

struct Node {
    int l, r;
    int pos;

    bool operator<(const Node src) const{
        if (l / block != src.l / block) return l < src.l;
        return ((l / block) & 1) ? r > src.r : r < src.r;
    }
};

Node node[N];

namespace Mos {
    int now;

    void Add(int x) {
        cnt[bucket[x]]--;
        cnt[++bucket[x]]++;
        while (cnt[now + 1]) now++;
    }
    void Delete(int x) {
        cnt[bucket[x]]--;
        cnt[--bucket[x]]++;
        while (!cnt[now]) now--;
    }
} using namespace Mos;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    block = sqrt(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        tmp[i] = a[i];
    }
    sort(tmp + 1, tmp + n + 1);
    int len = unique(tmp + 1, tmp + n + 1) - tmp - 1;
    for (int i = 1; i <= n; i++) a[i] = lower_bound(tmp + 1, tmp + len + 1, a[i]) - tmp;
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
    for (int i = 1; i <= n; i++) printf("%d\n", -ans[i]);
    return 0;
}