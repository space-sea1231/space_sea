#include <iostream>
#include <stdio.h>
#include <algorithm>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, m;
int f[N];
struct Node {
    int l, a, r;
    int pos;
};
Node node[N];

namespace BinaryTree {
    int sum[N];

    int Lowbit(int x) {
        return x & -x;
    }
    void Add(int x, int y){
        for (int i = x; i < N; i += Lowbit(i)) sum[i] = max(sum[i], y);
        return;
    }
    void Clear(int x) {
        for (int i = x; i < N; i += Lowbit(i)) sum[i] = 0;
        return;
    }
    int Query(int x) {
        int rev = 0;
        for (int i = x; i >= 1; i -= Lowbit(i)) rev = max(rev, sum[i]);
        return rev;
    }
} using namespace BinaryTree;

bool CmpA(Node srca, Node srcb) {
    return srca.a < srcb.a;
}
bool CmpL(Node srca, Node srcb) {
    return srca.l < srcb.l;
}
bool CmpP(Node srca, Node srcb) {
    return srca.pos < srcb.pos;
}
void Cdq(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    Cdq(l, mid);
    sort(node + l, node + mid + 1, CmpA);
    sort(node + mid + 1, node + r + 1, CmpL);
    int pos = l;
    for (int i = mid + 1; i <= r; i++) {
        while (pos <= mid && node[pos].a <= node[i].l) {
            Add(node[pos].r, f[node[pos].pos]);
            pos++;
        }
        f[node[i].pos] = max(f[node[i].pos], Query(node[i].a) + 1);
    }
    for (int i = l; i < pos; i++) Clear(node[i].r);
    sort(node + l, node + r + 1, CmpP);
    Cdq(mid + 1, r);
    return;
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> node[i].a;
        node[i].l = node[i].r = node[i].a;
        node[i].pos = i;
    }
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        node[x].l = min(node[x].l, y);
        node[x].r = max(node[x].r, y);
    }
    for (int i = 1; i <= n; i++) f[i] = 1;
    Cdq(1, n);
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, f[i]);
    printf("%d\n", ans);
    return 0;
}
/*
j 
aj<li
rj<ai; 
*/