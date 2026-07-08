#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e2 + 10;

int n, m;
int a[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    int siz = n * m;
    for (int i = 1; i <= siz; i++) cin >> a[i];
    int g = a[1];
    sort(a + 1, a + siz + 1);
    int pos = siz - (lower_bound(a + 1, a + siz + 1, g) - a) + 1;
    cerr<<pos;
    int x = pos % n, y = pos / n + 1;
    if (x == 0) y--, x = n;
    printf("%d %d\n", y, (y % 2) ? x : n - x + 1);
    return 0;
}