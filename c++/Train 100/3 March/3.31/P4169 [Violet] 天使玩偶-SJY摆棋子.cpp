#include <iostream>
#include <stdio.h>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 3e5 + 10;
const int LEN = 1e6 + 10;
const int INF = 0x3f3f3f3f;
int n, m;
int ans[N << 1];
struct Node {
    int x, y, opt;
    int id;
};
Node node[N << 1], cpy[N << 1], tmp[N << 1];

namespace BinaryTree {
    int sum[LEN];

    int Lowbit(int x) {
        return x & -x;
    }
    void Add(int x, int y) {
        for (int i = x; i < LEN; i += Lowbit(i)) sum[i] = max(sum[i], y);
        return;
    }
    void Clear(int x) {
        for (int i = x; i < LEN; i += Lowbit(i)) sum[i] = 0;
        return;
    }
    int Query(int x) {
        int rev = 0;
        for (int i = x; i >= 1; i -= Lowbit(i)) rev = max(rev, sum[i]);
        return rev == 0?-INF : rev;
    }
} using namespace BinaryTree;
void Cdq(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    Cdq(l, mid), Cdq(mid + 1, r);
    int ptr = l, num = l;
    for (int i = mid + 1; i <= r; i++) {
        while (ptr <= mid && cpy[ptr].x <= cpy[i].x) {
            if (cpy[ptr].opt == 1) Add(cpy[ptr].y, cpy[ptr].x + cpy[ptr].y);
            tmp[num++] = cpy[ptr];
            ptr++;
        }
        if (cpy[i].opt == 2) ans[cpy[i].id] = min(ans[cpy[i].id], cpy[i].x + cpy[i].y - Query(cpy[i].y));
        tmp[num++] = cpy[i];
    }
    for (int i = l; i < ptr; i++) {
        if (cpy[i].opt == 1) Clear(cpy[i].y);
    }
    for (int i = ptr; i <= mid; i++) tmp[num++] = cpy[i];
    for (int i = l; i <= r; i++) cpy[i] = tmp[i];
    return;
}
void Solve(bool flag1, bool flag2) {
    for (int i = 1; i <= n + m; i++) {
        cpy[i] = node[i];
        cpy[i].id = i;
        if (flag1) cpy[i].x = LEN - cpy[i].x;
        if (flag2) cpy[i].y = LEN - cpy[i].y;
    }
    Cdq(1, n + m);
    return;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> node[i].x >> node[i].y;
        node[i].x++, node[i].y++;
        node[i].opt = 1;
    }
    for (int i = n + 1; i <= n + m; i++) {
        cin >> node[i].opt >> node[i].x >> node[i].y;
        node[i].x++, node[i].y++;
    }
    memset(ans, INF, sizeof(ans));
    Solve(0, 0), Solve(0, 1), Solve(1, 0), Solve(1, 1);
    for (int i = n + 1; i <= n + m; i++) {
        if (node[i].opt == 2) printf("%d\n", ans[i]);
    }
    return 0;
}