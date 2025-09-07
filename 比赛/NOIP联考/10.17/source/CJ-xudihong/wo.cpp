#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
int T, n, a[2000005], ans = 1, cnt2 = 0, cnt1 = 0;
bool vis[2000005];
signed main()
{
    freopen("wo.in", "r", stdin);
    freopen("wo.out", "w", stdout);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        cnt2 = cnt1 = 0;
        ans = 1;
        for (int i = 0; i < n * 2; i++)
            cin >> a[i];
        for (int i = 0; i < n * 2; i++)
        {
            if (a[i])
            {
                if (a[i] <= n)
                {
                    cnt1++;
                }
                else
                {
                    cnt2++;
                }
            }
        }
        cnt1 = n - cnt1;
        cnt2 = n - cnt2;
        ans = 1;
        for (int x = 0; x < n * 2; x++)
        {
            if (a[x])
            {
                int lst = (x ^ 1);
                vis[x] = 1;
                vis[lst] = 1;
                if (a[x] <= n)
                {
                    if (!a[lst])
                    {
                        if (cnt2 > 0)
                            ans = ans * (cnt2) % MOD, cnt2--;
                        else
                            cnt1--;
                    }
                }
                else
                {
                    if (!a[lst])
                    {
                        if (cnt1 > 0)
                            ans = ans * (cnt1) % MOD, cnt1--;
                        else
                            cnt2--;
                    }
                }
            }
        }
        // cout << cnt1 << ' ' << cnt2 << '\n';
        cnt1 = (cnt1 + cnt2) / 2, cnt2 = cnt1;
        for (int i = 0; i < n * 2; i++)
        {
            if (vis[i])
            {
                continue;
            }
            int lst = (i ^ 1);
            vis[i] = vis[lst] = 1;
            if (cnt1 > 0 && cnt2 > 0)
                ans = ans * min(cnt1, cnt2) % MOD * min(cnt1, cnt2) % MOD * 2 % MOD, cnt1--, cnt2--;
            else
            {
                if (cnt1 > 0)
                    cnt2 = cnt1 / 2, cnt1 = cnt1 / 2;
                else if (cnt2 > 0)
                    cnt1 = cnt2 / 2, cnt2 = cnt2 / 2;
                ans = ans * cnt1 % MOD * cnt2 % MOD * 2 % MOD, cnt1--, cnt2--;
            }
        }
        printf("%lld\n", ans);
        for (int i = 0; i < n * 2; i++)
        {
            vis[i] = 0;
            a[i] = 0;
        }
    }
    return 0;
}