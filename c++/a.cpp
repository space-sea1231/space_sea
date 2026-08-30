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
const int N = 1e4 + 10;

int n, m, q;
vector<pair<int, int> > e[N], block[N << 1];
namespace Tarjan_ {
    int num, top, cnt;
    int dfn[N], low[N];
    int stk[N];

    void Tarjan(int u) {
        dfn[u] = low[u] = ++num;
        stk[++top] = u;
        for (auto [v, w]:e[u]) {
            if (!dfn[v]) {
                Tarjan(v);
                low[u] = min(low[u], low[v]);
                if (low[v] == dfn[u]) {
                    cerr << v << " " << u << " " << low[v] << endl;
                    cnt++;
                    while (stk[top] != u) {
                        block[cnt].emplace_back(make_pair(stk[top], 0));
                        block[stk[top]].emplace_back(make_pair(cnt, 0));
                        printf("%d %d\n", cnt, stk[top]);
                        top--;
                    }
                    block[cnt].emplace_back(make_pair(stk[top], 0));
                    block[stk[top]].emplace_back(make_pair(cnt, 0));
                    printf("%d %d\n", cnt, stk[top]);
                }
            } else low[u] = min(low[u], dfn[v]);
        }
    }
} using namespace Tarjan_;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> q; cnt = n;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].emplace_back(make_pair(v, w));
        e[v].emplace_back(make_pair(u, w));
    }
    for (int i = 1; i <= n; i++) if (!dfn[i]) Tarjan(i);
    for (int i = 1; i <= n; i++) printf("dfn[%d]=%d low[%d]=%d\n", i, dfn[i], i, low[i]);
    // for (int i = 1; i <= n; i++) 
    return 0;
}