#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 20;

int n;
int lim;
int a[N], b[N];
bool flag;

int H() {
    int rev = 0;
    for (int i = 1; i <= n; i++) if (abs(a[i] - a[i + 1]) != 1) rev++;
    return rev;
}
void Dfs(int dep, int sta, int last) {
    if (dep > lim) {
        if (!sta) flag = true;
        return;
    }
    for (int i = 2; i <= n; i++) {
        if (i == last || abs(a[i] - a[i + 1]) == 1) continue;
        reverse(a + 1, a + i + 1);
        int cur = sta;
        if (abs(a[i] - a[i + 1]) == 1) cur--;
        if (cur + dep <= lim) Dfs(dep + 1, cur, i);
        reverse(a + 1, a + i + 1);
        if (flag) return;
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    a[n + 1] = n + 1;
    sort(b + 1, b + n + 1);
    int len = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + len + 1, a[i]) - b;
    while (++lim) {
        Dfs(1, H(), 0);
        if (flag) {printf("%d\n", lim); return 0;}
    }
    return 0;
}
/*

*/