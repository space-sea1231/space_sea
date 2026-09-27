#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e5 + 10;

int n, m;
int cntA, cntB;
bool A[N], B[N];
bool vis[N];
vector<int> e[N];
stack<int> path;

void End() {
    printf("%d %d\n", n - cntA - cntB, cntA);
    while (!path.empty()) {
        printf("%d ", path.top());
        path.pop();
    }
    printf("\n");
    for (int i = 1; i <= n; i++) if (A[i]) printf("%d ", i);
    printf("\n");
    for (int i = 1; i <= n; i++) if (B[i]) printf("%d ", i);
    printf("\n");
    exit(0);
}
void Dfs(int u) {
    vis[u] = true;
    path.push(u);
    A[u] = false; cntA--;
    if (cntA == cntB) End();
    for (int v:e[u]) {
        if (vis[v]) continue;
        Dfs(v);
    }
    path.pop();
    B[u] = true; cntB++;
    if (cntA == cntB) End();
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) A[i] = true;
    cntA = n;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    Dfs(1);
    return 0;
}