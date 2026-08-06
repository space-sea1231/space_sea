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

int t, n, m;
int val[N][N];
int sta_bottom[40] = {21,20,20,18,20,14,18,13,20,18,14,13,18,13,13,7,20,18,18,15,18,13,13,11,18,15,13,11,15,11,11,6};
int sta_mid[20] = {14,13,13,11,13,7,11,6,13,11,7,6,11,6,6,0};
int sta_up[20] = {20,18,18,15,18,13,15,11,18,15,13,11,15,13,11,6};

struct Node {
    int val, id;

    bool operator<(const Node &s) const {return val < s.val;}
}; Node node[5];
ll Calc(int high) {
    int cur = (high == 1 ? 0 : 16);
    ll rev = 0;
    for (int i = 0; i < 4; i++) if (node[i].val) cur += (1 << node[i].id);
    rev += sta_bottom[cur], cur = 15;
    if (high == 1) return rev;

    int top = 0, last = 1;
    // Debug(high);
    while (top < 4 && high >= node[top].val) {
        rev += (ll)sta_mid[cur] * (node[top].val - last);
        while (node[top].val == node[top + 1].val) {
            cur -= (1 << node[top].id);
            // cerr<<node[top].id << endl;
            top++;
        }
        cur -= (1 << node[top].id);
        // cerr<<node[top].id << endl;
        last = max(1, node[top].val); top++;
    }
    // cerr<<endl;
    // if (top == 4) return rev + (high - 1 - node[top - 1].val) * sta_mid[cur] + sta_up[cur];
    // printf("Debug: %d %d\n", sta_up[cur], cur);
    return rev + (ll)(high - 1 - node[max(top - 1, 0)].val) * sta_mid[cur] + sta_up[cur];
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    node[4].val = -1;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> val[i][j];
            }
        }
        for (int i = 1; i <= n; i++) val[i][m + 1] = 0;
        for (int i = 1; i <= m; i++) val[n + 1][i] = 0;
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (!val[i][j]) continue;
                // cerr<<i << " " << j << endl;
                int w = (i == 1 ? 0 : val[i - 1][j]);
                int s = (i == n ? 0 : val[i + 1][j]);
                int a = (j == 1 ? 0 : val[i][j - 1]);
                int d = (j == m ? 0 : val[i][j + 1]);
                node[0] = (Node){w, 0};
                node[1] = (Node){d, 1};
                node[2] = (Node){s, 2};
                node[3] = (Node){a, 3};
                sort(node, node + 4);
                ll res = Calc(val[i][j]);
                ans += res;
                // printf("%d ", res);
            }
            // printf("\n");
        }
        printf("%lld\n", ans);
    }
    return 0;
}