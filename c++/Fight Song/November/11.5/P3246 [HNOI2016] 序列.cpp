#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
const int K = 18;

int n, m;
ll a[N];

// 栈
int top;
int stk[N];

// 单调栈预处理
ll fl[N], fr[N];
ll sfl[N], sfr[N];

// 笛卡尔树
namespace Tree {
    int root;
    int f[N][K];

    struct Node {
        int dep;
        int lson, rson;
    }; Node node[N];

    void Dfs(int u, int fa) {
        node[u].dep = node[fa].dep + 1;
        f[u][0] = fa;
        for (int i = 1; i < K; i++) f[u][i] = f[f[u][i - 1]][i - 1];
        if (node[u].lson) Dfs(node[u].lson, u);
        if (node[u].rson) Dfs(node[u].rson, u);
    }

    // 笛卡尔树的 LCA 就是区间 [x, y] 最小值的下标
    int Lca(int x, int y) {
        if (node[x].dep < node[y].dep) swap(x, y);
        for (int i = K - 1; ~i; i--) {
            if (node[f[x][i]].dep >= node[y].dep) {
                x = f[x][i];
            }
        }
        if (x == y) return x;
        for (int i = K - 1; ~i; i--) {
            if (f[x][i] != f[y][i]) {
                x = f[x][i];
                y = f[y][i];
            }
        }
        return f[x][0];
    }
} using namespace Tree;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];

    // 1. 建笛卡尔树，并顺便维护以 i 结尾的区间最小值和 fl[i]
    for (int i = 1; i <= n; i++) {
        int k = top;
        while (k && a[stk[k]] > a[i]) k--;
        if (k) node[stk[k]].rson = i;
        if (k < top) node[i].lson = stk[k + 1];
        
        // stk[k] 就是 i 左侧第一个比它小的位置
        int pre = stk[k];
        fl[i] = fl[pre] + a[i] * (i - pre);
        sfl[i] = sfl[i - 1] + fl[i];

        stk[++k] = i; 
        top = k;
    }

    // 2. 反向维护以 i 开头的区间最小值和 fr[i]
    top = 0;
    for (int i = n; i >= 1; i--) {
        while (top && a[stk[top]] > a[i]) top--;
        int nxt = top ? stk[top] : n + 1;
        fr[i] = fr[nxt] + a[i] * (nxt - i);
        stk[++top] = i;
    }
    for (int i = 1; i <= n; i++) sfr[i] = sfr[i - 1] + fr[i];

    // 3. 笛卡尔树预处理倍增 LCA
    Dfs(root = stk[1], 0);

    // 4. 回答询问：单次 O(log n)，总共 O(m log n)，飞速通过
    while (m--) {
        int l, r;
        cin >> l >> r;
        int p = Lca(l, r); // 找到区间 [l, r] 最小值的下标 p

        ll left = (sfr[p - 1] - sfr[l - 1]) - (ll)(p - l) * fr[p];
        ll right = (sfl[r] - sfl[p]) - (ll)(r - p) * fl[p];
        ll mid = a[p] * (ll)(p - l + 1) * (r - p + 1);

        cout << left + right + mid << "\n";
    }

    return 0;
}