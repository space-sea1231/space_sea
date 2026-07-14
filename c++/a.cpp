#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define int long long
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int t, n;
int minn[N];
int ansa[N], ansb[N];
int num;
vector<int> e[N];

int Dfs(int u) {
    minn[u] = u;
    for (auto v:e[u]) minn[u] = min(minn[u], Dfs(v));
    return u;
}
bool cmp(int a, int b) {
    return minn[a] > minn[b];
}
void Dfsa(int u) {
    ansa[u] = num--;
    for (auto v:e[u]) Dfsa(v);
}
void Dfsb(int u) {
    ansb[u] = num--;
    for (auto v:e[u]) Dfsb(v);
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            e[i].clear();
            minn[i] = INF;
        }
        for (int i = 2; i <= n; i++) {
            int u;
            cin >> u;
            e[u].emplace_back(i);
        }
        Dfs(1);
        for (int i = 1; i <= n; i++) sort(e[i].begin(), e[i].end(), cmp);
        num = n;
        Dfsa(1);
        for (int i = 1; i <= n; i++) reverse(e[i].begin(), e[i].end());
        num = n;
        Dfsb(1);
        for (int i = 1; i <= n; i++) printf("%d %d ", ansa[i], ansb[i]);
        printf("\n");
        // cerr<<t;
    }
    return 0;
}