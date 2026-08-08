#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e3 + 10;
const int K = 63;

int n;
int ans;

struct Node {
    ll id;
    int val;

    bool operator<(const Node &s) const {
        if (val == s.val) return id > s.id;
        return val > s.val;
    }
}; Node node[N];

namespace Linear_Basis {
    ll p[K];

    bool Insert(ll x) {
        for (int i = K - 1; i >= 0; i--) {
            if (x & (1LL << i)) {
                if (p[i]) x ^= p[i];
                else {p[i] = x; return true;}
            }
        }
        return false;
    }
} using namespace Linear_Basis;
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> node[i].id >> node[i].val;
    sort(node + 1, node + n + 1);
    for (int i = 1; i <= n; i++) if (Insert(node[i].id)) ans += node[i].val;
    printf("%d\n", ans);
    return 0;
}