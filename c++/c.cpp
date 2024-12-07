#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 10;
int t, n, a[MAXN];
int s[MAXN], pre[MAXN], suf[MAXN], ans;
int main()
{
    cin >> t;
    while (t--)
    {
        scanf("%d", &n);
        ans = suf[n + 1] = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &a[i]);
        }
        for (int i = 1; i <= n; i++)
            pre[i] = max(pre[i - 1] - 1, a[i]);
        for (int i = n; i; i--)
            suf[i] = max(suf[i + 1] - 1, a[i]);
        for (int i = 2; i < n; i++)
            ans = max(ans, pre[i - 1] + a[i] + suf[i + 1]);
        printf("%d\n", ans - 2);
    }
}