#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 5e5 + 5;
const int MOD  = 1e9 + 7;

int n;
ll a[MAXN], range[MAXN];
int l[MAXN], r[MAXN];
ll ans;
    
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", &a[i], &range[i]);
        l[i] = r[i] = i;
    }

    for (int i = 2; i <= n; i++) {
        while (l[i] > 1 && a[i] - a[l[i] - 1] <= range[i]) {
            range[i] = max(range[i], range[l[i] - 1] - (a[i] - a[l[i] - 1]));
            l[i] = l[l[i] - 1];
        }
    }

    for (int i = n - 1; i >= 1; i--) {
        while (r[i] < n && a[r[i] + 1] - a[i] <= range[i]) {
            l[i] = min(l[i], l[r[i] + 1]);
            r[i] = r[r[i] + 1];
        }
    }

    for (int i = 1; i <= n; i++) {
        ans = (ans + 1LL * i * (r[i] - l[i] + 1)) % MOD;
    }

    printf("%lld\n", ans);
    return 0;
}