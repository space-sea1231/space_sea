#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;
const int K = 18;
// const int base = 131;

char s[N];
int n, m = 122;
int x[N], y[N], h[N][K];
int cnt[N], ans[N], sa[N], lg[N];
int posL[N], posR[N];
// sa->排名第i的后缀起始位置
// x->后缀起始位置为i的排名
// y->第二关键字排名为i的起始位置

int Min(int l, int r) { // 排名l和r的后缀的最长公共前缀
    if (l == r) return n - sa[l] + 1;
    if (l > r) swap(l, r);
    if (!l || !r) return 0;
    l++;
    return min(h[l][lg[r - l + 1]], h[r - (1 << lg[r - l + 1]) + 1][lg[r - l + 1]]);
}
bool Check(int xl, int r, bool flag) { // 比较后缀l和r的大小（l<=r返回true）
    int l = sa[xl], xr = x[r], len = n - r + 1;
    int q1 = Min(xl, xr);
    if (q1 < len) return s[l + q1] < s[r + q1];
    int q2 = 0;
    if (l + len <= n) q2 = Min(x[l + len], xr);
    if (q2 < len) return s[l + len + q2] < s[r + q2];
    return flag;
}
namespace BinaryTree {
    int tree[N];

    int Lowbit(int x) { return x & -x; }
    void Update(int x, int y) {
        for (int i = x; i <= n + 1; i += Lowbit(i)) tree[i] += y;
    }
    int Query(int x) {
        int rev = 0;
        for (int i = x; i; i -= Lowbit(i)) rev += tree[i];
        return rev;
    }
} using namespace BinaryTree;
// ull p[N], h[N];
// int Hash(int l, int r) { return h[r] - h[l - 1] * p[r - l + 1]; }
signed main() {
    // freopen("ccfc.in", "r", stdin);
    // freopen("ccfc.out", "w", stdout);
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> (s + 1);
    n = strlen(s + 1); lg[0] = -1;
    for (int i = 1; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= n; i++) {
        x[i] = s[i];
        cnt[x[i]]++;
        // p[i] = p[i - 1] * base;
        // h[i] = h[i - 1] * base + s[i];
    }
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i; i--) sa[cnt[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int num = 0;
        for (int i = n - k + 1; i <= n; i++) y[++num] = i;
        for (int i = 1; i <= n; i++) if (sa[i] > k) y[++num] = sa[i] - k;
        for (int i = 1; i <= m; i++) cnt[i] = 0;
        for (int i = 1; i <= n; i++) cnt[x[i]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i; i--) {
            sa[cnt[x[y[i]]]--] = y[i];
            y[i] = 0;
        }
        swap(x, y);
        num = 1, x[sa[1]] = 1;
        for (int i = 2; i <= n; i++) {
            if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) x[sa[i]] = num;
            else x[sa[i]] = ++num;
        }
        if (num == n) break;
        m = num;
    }
    // for (int i = 1; i <= n; i++) printf("sa[%d]=%d\n", i, sa[i]);
    for (int i = 1, k = 0; i <= n; i++) {
        if (x[i] == 1) {
            h[x[i]][0] = 0;
            k = 0;
        } else {
            if (k) k--;
            while (s[i + k] == s[sa[x[i] - 1] + k]) k++;
            h[x[i]][0] = k;
        }
    }
    // for (int i = 1; i <= n; i++) printf("h[%d]=%d\n", i, h[i][0]);
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            h[i][k] = min(h[i][k - 1], h[i + (1 << k - 1)][k - 1]);
        }
    }
    for (int i = n; i > n - (n - 1) / 3; i--) { // i~n
        int l = 1, r = n, pos1 = 0; // pos1是最后一个<=的
        while (l <= r) {
            int mid = l + r >> 1;
            if (Check(mid, i, true)) {
                l = mid + 1;
                pos1 = mid;
            } else r = mid - 1;
        }
        l = 1, r = n; int pos2 = 0; // pos2是最后一个<的
        while (l <= r) {
            int mid = l + r >> 1;
            if (Check(mid, i, false)) {
                l = mid + 1;
                pos2 = mid;
            } else r = mid - 1;
        }
        posL[i] = pos2 + 1, posR[i] = pos1;
    }
    int ptr = n;
    for (int cur = n; cur >= 1; cur--) {
        while (ptr > n - (n - 1) / 3 && 3 * ptr - 2 * n - 3 >= cur) {
            if (posL[ptr] <= posR[ptr]) Update(posL[ptr], 1), Update(posR[ptr] + 1, -1);
            ptr--;
        }
        ans[cur] = Query(x[cur]);
    }
    for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
    return 0;
}