#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, a[400005], ans, now;
signed main()
{
    freopen("wei.in", "r", stdin);
    freopen("wei.out", "w", stdout);
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", a + i);
        }
        ans = now = 0;
        now = 1;
        int lst = 1;
        for (int i = 2; i <= n; i++)
        {
            if (a[i] < a[i - 1])
                lst = i;
            now += (i - lst + 1);
        }
        ans = now;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                swap(a[i], a[j]);
                now = 1;
                lst = 1;
                for (int k = 2; k <= n; k++)
                {
                    if (a[k] < a[k - 1])
                    {
                        lst = k;
                    }
                    now += (k - lst + 1);
                }
                ans = max(ans, now);
                swap(a[i], a[j]);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}