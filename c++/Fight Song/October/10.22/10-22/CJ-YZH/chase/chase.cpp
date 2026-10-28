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
const int N = 2e5 + 10;

int n, X, Y;
vector<int> e1[N], e2[N];


signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> X >> Y;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e1[u].emplace_back(v);
        e1[v].emplace_back(u);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e2[u].emplace_back(v);
        e2[v].emplace_back(u);
    }
    if (X < Y) printf("%d\n", (Y - 1) * 2);
    if (X > Y) printf("%d\n", (n - Y) * 2);
    if (X == Y) printf("0\n");
    return 0;
}