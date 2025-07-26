#include<bits/stdc++.h>
#define int long long
using namespace std;
char x_x;
const int N = 2e6 + 5, Mod = 998244353;
int n, cnt, cntt, a[N], num[2], tot[2], fac[N];
vector<bool> vis, v;
int quickpow(int a, int b)
{
    int res = 1;
    while(b)
    {
        if(b & 1)
            res = res * a % Mod;
        a = a * a % Mod;
        b >>= 1;
    }
    return res;
}
int inv(int x)
{
    return quickpow(x, Mod - 2);
}
int C(int n, int m)
{
    if(n < m)
        return 0;
    return fac[n] * inv(fac[m]) % Mod * inv(fac[n - m]) % Mod;
}
char y_y;
// #define debug
signed main()
{
    freopen("wo.in", "r", stdin);
    freopen("wo.out", "w", stdout);
    cin.tie(0) -> sync_with_stdio(0);
    fac[0] = 1;
    for(int i = 1; i <= 1e6; i++)
        fac[i] = fac[i - 1] * i % Mod;
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n;
        cnt = num[0] = num[1] = tot[0] = tot[1] = cntt = 0;
        vis.clear(), vis.resize(n << 1 | 1);
        v.clear(), v.resize(n << 1 | 1);
        for(int i = 1; i <= (n << 1); i += 2)
        {
            int x, y;
            cin >> x >> y;
            a[i] = x, a[i + 1] = y;
            v[x] = v[y] = 1;
            if(!x || !y)
                cntt++;
            else
                vis[x] = vis[y] = 1;
        }
        int it = 0, k = 0;
        for(int i = 1; i <= (n << 1); i++)
        {
            if(!vis[i])
            {
                it++;
                if(it == cntt)
                    k = i;
                if(!v[i])
                {
                    tot[it > cntt]++;
                // cerr << i << ' ' << it << endl;
                }
            }
        }
        // cerr << '\n';
        // cerr << k << endl;
        for(int i = 1; i <= (n << 1); i += 2)
        {
            int x = a[i], y = a[i + 1];
            if(x > y)
                swap(x, y);
            if(!x && y)
            {
                if(y > k)
                    num[0]++;
                else
                    num[1]++;
            }
            else if(!x && !y)
                cnt++;
        }
        // cerr << cntt << ' ' << tot[0] << ' ' << num[0] << ' ' << tot[1] << ' ' << num[1] << ' ' << cnt << endl;
        // cerr << C(tot[0], num[0]) * C(tot[1], num[1]) % Mod * fac[cnt] % Mod * quickpow(2, cnt) << endl;
        if(tot[0] < num[0])
            tot[1] -= (num[0] - tot[0]), tot[0] = num[0];
        if(tot[1] < num[1])
            tot[0] -= (num[1] - tot[1]), tot[1] = num[1];
        int ans = C(tot[0], num[0]) * fac[num[0]] % Mod * C(tot[1], num[1]) % Mod * fac[num[1]] % Mod * fac[cnt] % Mod * fac[cnt] % Mod * quickpow(2, cnt) % Mod;
        cout << ans << "\n";
    }
#ifdef debug
    cerr << (&x_x - &y_y) / 1024.0 / 1024.0 << " MB" << endl;
    cerr << (double)clock() / CLOCKS_PER_SEC << endl;
#endif
    return 0;
}