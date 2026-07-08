#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define int long long
using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e2 + 10;

int t, n;
int b[N], a[N];
int pre[N], nxt[N];
bool vis[N];

int Gcd(int a, int b) {
    while (b ^= a ^= b ^= a %= b);
    return a;
}
int Lcm(int a, int b) {
    return a / Gcd(a, b) * b;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> t;
    while (t--) {
        memset(vis, 0, sizeof(vis));
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(pre, 0, sizeof(pre));
        memset(nxt, 0, sizeof(nxt));
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> b[i];
        sort(b + 1, b + n + 1);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j < i; j++) {
                if (b[i] % b[j] == 0) {
                    vis[i] = true;
                }
            }
        }
        int tmp = n; n = 0;
        for (int i = 1; i <= tmp; i++) {
            if (!vis[i]) a[++n] = b[i];
        }
        // for (int i = 1; i <= n; i++) printf("a[%lld]=%lld\n", i, a[i]);
        for (int i = 1; i <= n; i++) {
            if (i != 1) pre[i] = a[i - 1];
            if (i != n) nxt[i] = a[i + 1];
        }
        int d = a[1];
        for (int i = 1; i <= n; i++) {
            d = Gcd(d, a[i]);
            for (int j = 1; j < i; j++) pre[i] = Lcm(pre[i], a[j]);
            for (int j = i + 1; j <= n; j++) nxt[i] = Gcd(nxt[i], a[j]);
        }
        // cerr<<t << " " << d<<endl;
        if (a[1] == 1 || d == a[1]) {
            printf("%lld\n", tmp - 1);
            continue;
        }
        bool flag = false;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j < i; j++) {
                if (d % (a[i] % a[j]) == 0) {
                    flag = true;
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j < i; j++) {
                if (a[i] % a[j] == 1) {
                    flag = true;
                    continue;
                }
            }
            if (nxt[i] >= a[i] && pre[i] <= a[i]) {
                // cerr << i << " " << n << endl;
                if (i == 1 || i == n) flag = true;
                else if (nxt[i] % pre[i] == 0) flag = true;
            }
        }
        if (flag) printf("%lld\n", tmp);
        else printf("%lld\n", tmp + 1);
    }
    return 0;
}