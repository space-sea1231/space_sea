#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <stack>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e7 + 10;

int n;
int l[N], r[N];
int a[N], s[N];

int read() {
    char c = getchar();
    bool flag = 0;
    int rev = 0;
    for (; !isdigit(c); c = getchar()) if (c == '-') flag = true;
    for (; isdigit(c); c = getchar()) rev = (rev << 1) + (rev << 3) + (c ^ 48);
    return rev * (flag ? -1 : 1);
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    // for (int i = 1; i <= n; i++) printf("%d\n", a[i]);
    int top = 0, cur = 0;
    for (int i = 1; i <= n; i++) {
        cur = top;
        while (cur && a[s[cur]] > a[i]) cur--;
        if (cur) r[s[cur]] = i;
        if (cur < top) l[i] = s[cur + 1];
        s[++cur] = i;
        top = cur;
    }
    ll ans1 = 0, ans2 = 0;
    // for (int i = 1; i <= n; i++) printf("l[%d]=%d r[%d]=%d\n", i, l[i], i, r[i]);
    for (int i = 1; i <= n; i++) ans1 ^= (ll)i * (l[i] + 1);
    for (int i = 1; i <= n; i++) ans2 ^= (ll)i * (r[i] + 1);
    printf("%lld %lld\n", ans1, ans2);
    return 0;
}