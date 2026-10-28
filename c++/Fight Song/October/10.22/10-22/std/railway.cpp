#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7, logN = 21;
int n, k, q, l[N];
int stk[N], tt;
int L[N][logN], R[N][logN];
int query(int a, int b) {
    if (a > b)
        swap(a, b);
    int l = a, r = a, ans = 0;
    for (int i = logN - 1; i >= 0; i --) {
        if (max(R[l][i], R[r][i]) < b) {
            int tl = l, tr = r;
            l = min(L[tl][i], L[tr][i]);
            r = max(R[tl][i], R[tr][i]);
            ans += (1 << i);
        }
    }
    int u = b, v = b;
    for (int i = logN - 1; i >= 0; i --) {
        if (min(L[u][i], L[v][i]) > r) {
            int tl = u, tr = v;
            u = min(L[tl][i], L[tr][i]);
            v = max(R[tl][i], R[tr][i]);
            ans += (1 << i);
        }
    }
    return ans;
}
int main() {
    freopen("railway.in","r",stdin);
    freopen("railway.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> k >> q;
    for (int i = 1; i <= n; i ++)
        cin >> l[i];
    for (int i = 1; i <= n; i ++) {
        int pre = 0;
        while (tt && l[stk[tt]] <= l[i]) {
            if (!pre && l[stk[tt]] == l[i])
                pre = stk[tt]; //左边第一个齐平的
            R[stk[tt --]][0] = i; // 右边第一个>=的牌
        }
        L[i][0] = (pre ? pre : stk[tt]);
        stk[++ tt] = i;
    }
    while (tt)
        R[stk[tt --]][0] = n + 1;
    
    L[1][0] = 1, R[n][0] = n;
    for (int j = 1; j < logN; j ++) {
        for (int i = 1; i <= n; i ++) {
            L[i][j] = min(L[L[i][j - 1]][j - 1], L[R[i][j - 1]][j - 1]);
            R[i][j] = max(R[R[i][j - 1]][j - 1], R[L[i][j - 1]][j - 1]);
        }
    }
    // for (int j = 0; j < logN; j ++) {
    //     for (int i = 1; i <= n; i ++)
    //         cerr << L[i][j] << ' ';
    //     cerr << '\n';
    // }
    // cerr << "\n";
    // for (int j = 0; j < logN; j ++) {
    //     for (int i = 1; i <= n; i ++)
    //         cerr << R[i][j] << ' ';
    //     cerr << '\n';
    // }

    while (q --) {
        int a, b;
        cin >> a >> b;
        cout << query(a, b) + (a != b) << '\n';
    }
    return 0;
}