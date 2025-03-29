#include <bits/stdc++.h>
#define N 100005
#define mod 998442353
#define ll long long 
#define rint register int 
#define rll register long long 
static char buf[8388608], *P1 = buf, *P2 = buf, obuf[8388608], *P3 = obuf;
#define getchar() P1 == P2 && (P2 = (P1 = buf) + fread(buf, 1, 8388608, stdin), P1 == P2) ? EOF : *P1 ++
#define putchar(c) (P3 - obuf < 8388608) ? (*P3 ++ = c) : (fwrite(obuf, 8388608, 1, stdout), P3 = obuf, *P3 ++ = c)
#define flush() fwrite(obuf, P3 - obuf, 1, stdout)
using namespace std;
inline void read(register char &c) {while ((c = getchar()) <= 32);}
inline void read(register char *s) {while ((*s = getchar()) <= 32) ; ++ s; while ((*s = getchar()) > 32) ++ s; *s = 0;}
inline void read(register string &s) {s = ""; register char c; while ((c = getchar()) > 32) s.push_back(c);}
template <typename T>
inline void read(register T &x)
{
    x = 0; register short flag = 1, ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) flag = (ch ^ '-' ? 1 : -1);
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ 48);
    x *= flag;
}
template<typename T, typename... More>
inline void read(T &x, More&... more) {read(x), read(more...);}
inline void print(register char *s) {while (*s) putchar(*s ++);}
inline void print(register const string s) {for (const char ch : s) putchar(ch);}
inline void print(register const char c) {putchar(c);}
template<typename T>
inline void print(register T x)
{
    if (x < 0) putchar('-'), x = ~(x - 1);
    if (x > 9) print(x / 10);
    putchar(x % 10 + 48);
}
template<typename T, typename... More>
inline void print(register T x, register More... more) {print(x), print(more...);}
inline void file(string s) {freopen((s + ".in").c_str(), "r", stdin), freopen((s + ".out").c_str(), "w", stdout);}
int T, n, m, fac[N << 5], inv[N << 5], f[1 << 16][16], g[1 << 16][16], p[16][16], cnt[1 << 16]; pair<int, int> dis[16][16];
inline int C(rint n, rint m) {return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;}
inline pair<int, int> calc(rint i, rint j)
{
    rint sum = 0, K = 1;
    for (rint k = 0; k < n; ++ k) K = 1ll * K * C((sum += abs(p[i][k] - p[j][k])), abs(p[i][k] - p[j][k])) % mod;
    return {sum, K};
}
inline void Add(rint &x, rint y) {(x += y) >= mod && (x -= mod);}
signed main()
{
    freopen("ge.in", "r", stdin);
    freopen("ge.out", "w", stdout);
    fac[0] = inv[0] = inv[1] = 1;
    for (rint i = 1; i <= 3200000; ++ i) fac[i] = 1ll * fac[i - 1] * i % mod;
    for (rint i = 2; i <= 3200000; ++ i) inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
    for (rint i = 2; i <= 3200000; ++ i) inv[i] = 1ll * inv[i - 1] * inv[i] % mod;
    for (rint i = 1; i < (1 << 16); ++ i) cnt[i] = cnt[i ^ (i & -i)] + 1;
    for (read(T); T --;)
    {
        read(n, m);
        for (rint i = 0; i < m; ++ i)
            for (rint j = 0; j < n; ++ j)
                read(p[i][j]);
        for (rint i = 0; i < (1 << m); ++ i)
            for (rint j = 0; j < m; ++ j)
                f[i][j] = 0x3f3f3f3f, g[i][j] = 0;
        register bool ok = false;
        for (rint i = 0, x; i < m; ++ i)
        {
            read(x);
            if (x) f[1 << i][i] = 0, g[1 << i][i] = 1, ok = true;
        }
        if (!ok) {print('N', 'I', 'E', '\n'); continue;}
        for (rint i = 0; i < m; ++ i)
            for (rint j = i + 1; j < m; ++ j)
                dis[i][j] = dis[j][i] = calc(i, j);
        for (rint i = 1; i < (1 << m); ++ i)
            for (rint j = 0; j < m; ++ j)
                if (cnt[i] >= 2 && i & (1 << j))
                {
                    rint cur = (i ^ (1 << j));
                    for (rint k = 0; k < m; ++ k)
                        if (cur & (1 << k))
                        {
                            rint d = f[cur][k] + dis[k][j].first;
                            if (d < f[i][j]) f[i][j] = d, g[i][j] = 1ll * g[cur][k] * dis[k][j].second % mod;
                            else if (d == f[i][j]) Add(g[i][j], 1ll * g[cur][k] * dis[k][j].second % mod);
                        }
                }
        rint resa = 2e9, resb = 0;
        for (rint i = 0; i < m; ++ i)
            if (f[(1 << m) - 1][i] < resa) resa = f[(1 << m) - 1][i], resb = g[(1 << m) - 1][i];
            else if (f[(1 << m) - 1][i] == resa) Add(resb, g[(1 << m) - 1][i]);
        print(resa, ' ', resb, '\n');
    }
    return flush(), 0;
}