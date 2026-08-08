#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 30;

int n;
int a[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int l = 0, r = 0;
    for (int i = 1; i <= n; l++, i++) if (!a[i]) break;
    for (int i = n; i; r++, i--) if (!a[i]) break;
    if (l == n && r == n) printf("%s\n", n % 2 ? "YES" : "NO");
    else printf("%s\n", (l + r) % 2 ? "YES" : "NO");
    return 0;
}