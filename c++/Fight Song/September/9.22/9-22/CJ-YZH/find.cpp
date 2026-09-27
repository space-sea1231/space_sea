#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

int n, m;

signed main() {
    freopen("find.in", "r", stdin);
    freopen("find.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    printf("%d %d\n", n, 0);
    for (int i = 1; i <= n; i++) printf("%d ", i);
    return 0;
}