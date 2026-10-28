#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e3 + 10;
const int Mod = 1e9 + 7;

int n, m, k;
int fact[N], inv[N];
struct Node {
    int x, y;
    int val;
    bool operator<(const Node &s) const { return x + y < s.x + s.y; }
}; Node node[N];

int Pow(int a, int b) {
    int sum = 1;
    while (b) {
        if (b & 1) sum = (ll)sum * a % Mod;
        a = (ll)a * a % Mod;
        b >>= 1;
    }
    return sum;
}
int C(int n, int m) {
    if (n < m || m < 0) return 0;
    return (ll)fact[n] * inv[n - m] % Mod * inv[m] % Mod;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    fact[0] = 1; for (int i = 1; i <= n + m - 1; i++) fact[i] = (ll)fact[i - 1] * i % Mod;
    inv[n + m - 1] = Pow(fact[n + m - 1], Mod - 2); for (int i = n + m - 2; ~i; i--) inv[i] = (ll)inv[i + 1] * (i + 1) % Mod;
    int ans = C(n + m - 2, min(n, m) - 1);
    // cerr<<C(1,0)<<"\n";
    for (int i = 1; i <= k; i++) cin >> node[i].x >> node[i].y;
    sort(node + 1, node + k + 1);
    for (int i = 1; i <= k; i++) {
        int x = node[i].x, y = node[i].y;
        node[i].val = C(x + y - 2, min(x, y) - 1);
        for (int j = 1; j < i; j++) {
            int x = node[j].x, y = node[j].y;
            node[i].val = (node[i].val - (ll)node[j].val * C(node[i].x + node[i].y - x - y, min(node[i].x - x, node[i].y - y)) % Mod + Mod) % Mod;
        }
        // cerr<<node[i].val << "\n";
    }
    for (int i = 1; i <= k; i++) {
        int x = node[i].x, y = node[i].y;
        ans = (ans - (ll)node[i].val * C(n + m - x - y, min(n - x, m - y)) % Mod + Mod) % Mod;
        // cerr<<C(x + y - 2, min(x, y) - 1) * C(n + m - x - y, min(n - x, m - y))<<"\n";
    }
    printf("%d\n", ans);
    return 0;
}