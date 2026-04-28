#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 2e5 + 10;
const int M = 1e6 + 10;

int n, m;
int block;
int a[N];
int ans[N];
int cntn, cnto;

struct Node {
    int l, r;
    int pos, t;

    bool operator<(const Node src)const {
        if (l / block != src.l / block) return l < src.l;
        if (r / block != src.r / block) return r < src.r;
        return t < src.t;
        // return ((l / block) & 1) ? r < src.r : r > src.r;
    }
};
Node node[N];

struct Operation {
    int x, y;
};
Operation opt[N];

namespace Mos {
    int now;
    int cnt[M];

    void Add(int x) {
        cnt[x]++;
        if (cnt[x] == 1) now++;
        return;
    }
    void Delete(int x) {
        cnt[x]--;
        if (cnt[x] == 0) now--;
        return;
    }
} using namespace Mos;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    block = pow(n, 2.0 / 3.0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) {
        char c;
        int l, r;
        cin >> c >> l >> r;
        if (c == 'Q') node[++cntn] = (Node){l, r, cntn, cnto};
        if (c == 'R') opt[++cnto] = (Operation){l, r};
    }
    sort(node + 1, node + m + 1);
    int l = 1, r = 0, last;
    for (int i = 1; i <= m; i++) {
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
        ans[node[i].pos] = now;
    }
    for (int i = 1; i <= cntn; i++) printf("%d\n", ans[i]);
    return 0;
}