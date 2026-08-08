#include <cstdio>
#include <algorithm>

#define int long long

using namespace std;

const int N = 270005;
const int mod = 998244353;

int n, ans, tot, fac[N], ifa[N], p[N], vis[N], phi[N];
int m, I, l, lim, a[N], b[N], f[N], g[N], rev[N];

int Pow(int x, int y)
{
    int r = 1;
    for(; y; y >>= 1, x = x * x % mod)
        if(y & 1)
            r = r * x % mod;
    return r;
}

void Init(int n)
{
    fac[0] = ifa[0] = 1;
    for(int i = 1; i <= n; ++ i)
        fac[i] = fac[i - 1] * i % mod;
    ifa[n] = Pow(fac[n], mod - 2);
    for(int i = n - 1; i >= 1; -- i)
        ifa[i] = ifa[i + 1] * (i + 1) % mod;

    phi[1] = 1;
    for(int i = 2; i <= n; ++ i)
    {
        if(!vis[i])
            p[++ tot] = i, phi[i] = i - 1;
        for(int j = 1; j <= tot && i * p[j] <= n; ++ j)
        {
            vis[i * p[j]] = 1;
            if(i % p[j] == 0)
            {
                phi[i * p[j]] = phi[i] * p[j];
                break;
            }
            phi[i * p[j]] = phi[i] * (p[j] - 1);
        }
    }
}

int C(int n, int m)
{
    return fac[n] * ifa[m] % mod * ifa[n - m] % mod;
}

void init(int n)
{
    for(l = 0, lim = 1; lim < n; lim <<= 1, ++ l);
    I = Pow(lim, mod - 2);
    for(int i = 0; i < lim; ++ i)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
}

void NTT(int *a, int type)
{
    for(int i = 0; i < lim; ++ i)
        if(i < rev[i])
            swap(a[i], a[rev[i]]);
    for(int i = 1; i < lim; i <<= 1)
    {
        int x = Pow(type ? 3 : (mod + 1) / 3, (mod - 1) / (i << 1));
        for(int j = 0; j < lim; j += (i << 1))
        {
            for(int k = 0, y = 1; k < i; ++ k, y = y * x % mod)
            {
                int p = a[j + k], q = y * a[i + j + k] % mod;
                a[j + k] = (p + q) % mod;
                a[i + j + k] = (p - q + mod) % mod;
            }
        }
    }
    if(!type)
        for(int i = 0; i < lim; ++ i)
            a[i] = a[i] * I % mod;
}

signed main()
{
    Init(100000);
 
    int T;
    scanf("%lld", &T);
    while(T --)
    {
        scanf("%lld", &n);

        for(int i = 1; i <= n; ++ i)
            a[i] = b[i] = 0;
        for(int x = 1; x <= n; ++ x)
            for(int i = x; i <= n; i += x)
                (a[i] += phi[x] * (i / x)) %= mod;
                
        for(int x = 1; x <= n; ++ x)
        {
            m = n / x + 1;
            init(m + m);
            for(int i = 0; i < lim; ++ i)
                f[i] = g[i] = 0;
            g[0] = 1;
            for(int i = x, j = 1; i <= n; i += x, ++ j)
                f[j] = a[i] * ifa[i] % mod, g[j] = ifa[i];
            NTT(f, 1), NTT(g, 1);
            for(int i = 0; i < lim; ++ i)
                f[i] = f[i] * g[i] % mod;
            NTT(f, 0);
            for(int i = x, j = 1; i <= n; i += x, ++ j)
                (b[i] += phi[x] * f[j]) %= mod;
        }

        ans = 0;
        for(int i = 1; i <= n; ++ i)
            (ans += b[i] * fac[i]) %= mod;

        printf("%lld\n", (ans % mod + mod) % mod);

    }


    return 0;
}
