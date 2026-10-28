#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

int n;

signed main() {
    freopen("river.in", "r", stdin);
    freopen("river.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    if (n == 2) printf("-1\n");
    else if (n & 1) for (int i = 1; i <= n; i++) printf("%d ", i);
    else for (int i = 1; i <= n; i++) printf("%d ", ((i - 1) ^ 1) + 1);
    return 0;
}