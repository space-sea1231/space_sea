#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;
const ll Mod = 2147483648;

int n, m, W, k;
int tmpx[N], tmpy[N];
int C[N][11];
vector<int> qx[N], qy[N];

struct Node {
    int x, y;

    bool operator<(const Node &s) const {
        if (y == s.y) return x < s.x;
        return y < s.y;
    }
}; Node node[N];

namespace BinaryTree {
    int tree[N];

    int Lowbit(int x) { return x & -x; }
    void Add(int x, int y) {
        for (int i = x; i < N; i += Lowbit(i)) {
            tree[i] = ((ll)tree[i] + y) % Mod;
        }
    }
    int Query(int x) {
        int rev = 0;
        for (int i = x; i; i -= Lowbit(i)) rev = ((ll)rev + tree[i]) % Mod;
        return rev;
    }
} using namespace BinaryTree;
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> W;
    C[0][0] = 1;
    for (int i = 1; i <= W; i++) {
        C[i][0] = 1;
        for (int j = 1, lim = min(i, 10); j <= lim; j++) {
            C[i][j] = ((ll)C[i - 1][j - 1] + C[i - 1][j]) % Mod;
        }
    }
    for (int i = 1; i <= W; i++) {
        cin >> node[i].x >> node[i].y;
        tmpx[i] = node[i].x, tmpy[i] = node[i].y;
    }
    sort(tmpx + 1, tmpx + W + 1);
    sort(tmpy + 1, tmpy + W + 1);
    sort(node + 1, node + W + 1);
    int lenx = unique(tmpx + 1, tmpx + W + 1) - tmpx - 1;
    int leny = unique(tmpy + 1, tmpy + W + 1) - tmpy - 1;
    for (int i = 1; i <= W; i++) {
        node[i].x = lower_bound(tmpx + 1, tmpx + lenx + 1, node[i].x) - tmpx;
        node[i].y = lower_bound(tmpy + 1, tmpy + leny + 1, node[i].y) - tmpy;
        qx[node[i].x].emplace_back(node[i].y);
        qy[node[i].y].emplace_back(node[i].x);
        // cerr<<node[i].x << " " << node[i].y << "\n";
    }
    cin >> k;
    int ans = 0;
    // for (int v : qy[3]) printf("%d ", v); printf("\n");
    for (int i = 1; i <= leny; i++) {
        for (int j = k - 1, lim = (int)qy[i].size() - k; j < lim; j++) {
            ans = (ans + (ll)C[j + 1][k] * C[qy[i].size() - j - 1][k] % Mod * (Query(qy[i][j + 1] - 1) - Query(qy[i][j]) + Mod) % Mod) % Mod;
            // cerr<<qy[i][j + 1] - 1 << " " << qy[i][j] << " " << Query(qy[i][j + 1] - 1) - Query(qy[i][j]) << "\n";
            // cerr<<qy[i].size() << " " << j << "\n";
        }
        for (int j = 0, lim = qy[i].size(); j < lim; j++) {
            int x = qy[i][j], y = i;
            int pos = lower_bound(qx[x].begin(), qx[x].end(), y) - qx[x].begin();
            // printf("%d %d\n", i, pos);
            if (pos >= k && (int)qx[x].size() - pos >= k) Add(x, -C[pos][k] * C[qx[x].size() - pos][k]);
            if (pos + 1 >= k && (int)qx[x].size() - pos - 1 >= k) {
                // cerr<<C[pos + 1][k] << " " << C[(int)qx[x].size() - pos - 2][k] << "\n";
                Add(x, (ll)C[pos + 1][k] * C[(int)qx[x].size() - pos - 1][k] % Mod);
            }
        }
        // cerr<< i << " " << ans << "\n";
    }
    printf("%u\n", ans);
    return 0;
}