#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;
const int K = 19;

int n, k, q;
int top;
int a[N], stk[N];
int L[N][K], R[N][K];

int Query(int a, int b) {
    if (a > b) swap(a, b);
    int l = a, r = a, ans = 0;
    for (int i = K - 1; ~i; i--) {
        if (max(R[l][i], R[r][i]) < b) {
            int tl = l, tr = r;
            l = min(L[tl][i], L[tr][i]);
            r = max(R[tl][i], R[tr][i]);
            ans += (1 << i);
        }
    }
    int u = b, v = b;
    for (int i = K - 1; ~i; i--) {
        if (min(L[u][i], L[v][i]) > r) {
            int tl = u, tr = v;
            u = min(L[tl][i], L[tr][i]);
            v = max(R[tl][i], R[tr][i]);
            ans += (1 << i);
        }
    }
    return ans;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> k >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        int pre = 0;
        while (top && a[stk[top]] <= a[i]) {
            if (!pre && a[stk[top]] == a[i]) pre = stk[top];
            R[stk[top--]][0] = i;
        }
        L[i][0] = (pre ? pre : stk[top]);
        stk[++top] = i;
    }
    while (top) R[stk[top--]][0] = n + 1;
    L[1][0] = 1, R[n][0] = n;
    for (int l = 1; l < K; l++) {
        for (int i = 1; i <= n; i++) {
            L[i][l] = min(L[L[i][l - 1]][l - 1], L[R[i][l - 1]][l - 1]);
            R[i][l] = max(R[R[i][l - 1]][l - 1], R[L[i][l - 1]][l - 1]);
        }
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        printf("%d\n", Query(l, r) + (l != r));
    }
    return 0;
}