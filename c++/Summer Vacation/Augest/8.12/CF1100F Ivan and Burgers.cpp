#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 6e5 + 10;
const int K = 20;

int n, q;
int a[N];
int ans[N];
struct Node {
    int l, r;
    int pos;

    bool operator<(const Node &s) const {
        return r < s.r;
    }
}; Node node[N];

namespace Linear_Basis {
    int bit[K], pos[K];

    void Insert(int x, int p) {
        for (int i = K - 1; ~i; i--) {
            if ((1 << i) & x) {
                if (!bit[i]) {bit[i] = x; pos[i] = p; return;}
                else if (p > pos[i]) {swap(p, pos[i]); swap(x, bit[i]);}
                x ^= bit[i];
            }
        }
    }
    int Query(int p) {
        int rev = 0;
        for (int i = K - 1; ~i; i--) {
            if (((1 << i) & rev) == 0 && pos[i] >= p) {
                rev ^= bit[i];
            }
        }
        return rev; 
    }
} using namespace Linear_Basis;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> node[i].l >> node[i].r;
        node[i].pos = i;
    }
    sort(node + 1, node + q + 1);
    
    int last = 1;
    for (int i = 1; i <= q; i++) {
        for (int j = last; j <= node[i].r; j++) Insert(a[j], j);
        last = node[i].r + 1;
        ans[node[i].pos] = Query(node[i].l);
    }

    for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
    return 0;
}