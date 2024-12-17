#include <stdio.h>
using ll = long long;
const int N = 1e6 + 5, M = 998244353;
int p[N];
int main()
{
    freopen("wo.in", "r", stdin);
    freopen("wo.out", "w", stdout);
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n, cnt = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n + n; ++i)
        {
            scanf("%d", p + i);
            cnt += !p[i];
        }
        printf("%lld\n", cnt ? 1ll << cnt - 1 : 1);
    }
    return 0;
}
