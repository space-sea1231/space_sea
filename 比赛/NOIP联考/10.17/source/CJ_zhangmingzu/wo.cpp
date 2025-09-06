#include <bits/stdc++.h>
#define int long long
using namespace std;
void file(string x)
{
    freopen((x + ".in").c_str(), "r", stdin);
    freopen((x + ".out").c_str(), "w", stdout);
}
const int maxn = 2e6 + 5, mod = 998244353, inv2 = 499122177;
int p[maxn], n, fac[maxn], inv[maxn], pw[maxn];
int ksm(int x, int y)
{
    int ans = 1;
    while (y)
    {
        if (y & 1) ans = ans * x % mod;
        x = x * x % mod, y >>= 1;
    }
    return ans;
}
int C(int x, int y)
{
    return fac[x] * inv[y] % mod * inv[x - y] % mod;
}
void solve()
{
    cin >> n;
    int sum1 = n, sum2 = n;
    for (int i = 1; i <= 2 * n; i++)
    {
        cin >> p[i];
        if (p[i])
            p[i] <= n ? sum1-- : sum2--;
    }
    int ans = 1, os = 0, k2w = 0, k1wx = 0, k1wd = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!p[i * 2] && !p[i * 2 - 1])
        {
            ans = ans * 2 % mod;
            k2w++;
            continue;
        }
        if (!p[i * 2] || !p[i * 2 - 1])
        {
            max(p[i * 2], p[i * 2 - 1]) <= n ? k1wx++ : k1wd++;
            continue;
        }
        if (p[i * 2] <= n && p[i * 2 - 1] <= n) os--;
        if (p[i * 2] > n && p[i * 2 - 1] > n) os++;
    }
    ans = ans * fac[k2w] % mod;
    if (os <= 0)
    {
        for (; k1wx; sum2--, k1wx--)
            ans = ans * sum2 % mod;
        int sum = 0;
        for (int i = max(0ll, sum1 - k1wd); i <= sum1; i++)
        {
            int now = k1wd - (sum1 - i), sx = sum2 - now - i; //大于的需要补充这么多个，还剩下多少个大于的
            if (now > -os) continue;
            assert(!(sx & 1));
            if (sum2 >= now + i)
                sum = (sum + fac[sum1] % mod * C(k1wd, sum1 - i) % mod * (fac[sum2] * inv[sum2 - now] % mod) % mod * pw[sx / 2] % mod * (fac[sum2 - now] * inv[i] % mod) % mod);
        }
        ans = ans * sum % mod;
    }
    else
    {
        swap(k1wx, k1wd);
        swap(sum1, sum2);
        os = -os;
        for (; k1wx; sum2--, k1wx--)
            ans = ans * sum2 % mod;
        int sum = 0;
        for (int i = max(0ll, sum1 - k1wd); i <= sum1; i++)
        {
            int now = k1wd - (sum1 - i), sx = sum2 - now - i; //大于的需要补充这么多个，还剩下多少个大于的
            if (now > -os) continue;
            assert(!(sx & 1));
            if (sum2 >= now + i)
                sum = (sum + fac[sum1] % mod * C(k1wd, sum1 - i) % mod * (fac[sum2] * inv[sum2 - now] % mod) % mod * pw[sx / 2] % mod * (fac[sum2 - now] * inv[i] % mod) % mod);
        }
        ans = ans * sum % mod;
    }
    cout << ans << '\n';
}
signed main()
{
    file("wo");
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    fac[0] = inv[0] = pw[0] = 1;
    for (int i = 1; i < maxn; i++)
        fac[i] = fac[i - 1] * i % mod, pw[i] = pw[i - 1] * inv2 % mod;
    inv[maxn - 1] = ksm(fac[maxn - 1], mod - 2);
    for (int i = maxn - 2; i >= 1; i--) inv[i] = inv[i + 1] * (i + 1) % mod;
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}