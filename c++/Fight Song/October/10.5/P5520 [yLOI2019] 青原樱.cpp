#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e6 + 10;

int type, n, m, p;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> type >> n >> m >> p;
    int ans = 1;
    for (int i = n - m + 1; i > n - 2 * m + 1 && i; i--) ans = (ll)ans * i % p;
    printf("%d\n", ans);
    return 0;
}