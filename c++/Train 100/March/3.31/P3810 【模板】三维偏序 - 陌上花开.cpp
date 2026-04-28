#include <iostream>
#include <stdio.h>
#include <algorithm>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
int n, m;
int num;
int ans[N];
struct Node {
    int a, b, c;
    int ans, cnt;
    int id;

    bool operator!=(const Node src)const{
        return (a != src.a) || (b != src.b) || (c != src.c); 
    }
};
Node node[N], tmp[N];

namespace BinaryTree {
    ll sum[N << 1];

    int Lowbit(int x) {
        return x & -x;
    }
    void Add(int x, int y) {
        for (int i = x; i <= m; i += Lowbit(i)) sum[i] += y;
        return;
    }
    int Query(int x) {
        int rev = 0;
        for (int i = x; i >= 1; i -= Lowbit(i)) rev += sum[i];
        return rev;
    }
} using namespace BinaryTree;
bool CmpA(Node srca, Node srcb) {
    if (srca.a != srcb.a) return srca.a < srcb.a;
    if (srca.b != srcb.b) return srca.b < srcb.b;
    return srca.c < srcb.c;
}
bool CmpB(Node srca, Node srcb) {
    if (srca.b != srcb.b) return srca.b < srcb.b;
    return srca.c < srcb.c;
}
void Cdq(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    Cdq(l, mid), Cdq(mid + 1, r);
    sort(node + l, node + mid + 1, CmpB);
    sort(node + mid +1, node + r + 1, CmpB);
    int ptr = l;
    for (int i = mid + 1; i <= r; i++) {
        while (ptr <= mid && node[ptr].b <= node[i].b) {
            Add(node[ptr].c, node[ptr].cnt);
            ptr++;
        }
        node[i].ans += Query(node[i].c);
    }
    for (int i = l; i < ptr; i++) Add(node[i].c, -node[i].cnt);
    return;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> tmp[i].a >> tmp[i].b >> tmp[i].c;
        tmp[i].id = i;
    }
    sort(tmp + 1, tmp + n + 1, CmpA);
    int cnt = 1;
    for (int i = 1; i <= n; i++) {
        if (tmp[i] != tmp[i + 1]) {
            node[++num] = tmp[i];
            node[num].cnt = cnt;
            cnt = 1;
        }
        else cnt++;
    }
    Cdq(1, num);
    for (int i = 1; i <= num; i++) ans[node[i].ans + node[i].cnt - 1] += node[i].cnt;
    for (int i = 0; i < n; i++) printf("%d\n", ans[i]);
     
    return 0;
}