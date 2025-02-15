#include <bits/stdc++.h>
#define N 1000005
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
int T, n, dis[1 << 20], pre[1 << 20][2], q[1 << 20], S; char s[N];
inline void Print(rint u)
{
    if (!dis[u]) return ;
    Print(pre[u][0]);
    print(pre[u][1], ' ');
}
inline void bfs()
{
    memset(dis, 0x3f, sizeof(dis));
    S = 0;
    for (rint i = 1; i <= n; ++ i)
        if (s[i] ^ 48) S |= (1 << i - 1);
    rint h, t, mx = -1, T = 0; q[h = t = 1] = S, dis[S] = 0;
    while (h <= t)
    {
        rint u = q[h ++];
        if (__builtin_popcount(u) > mx) mx = __builtin_popcount(u), T = u;
        for (rint i = 1; i < n - 1; ++ i)
        {
            rint nxt = u;
            if (u & (1 << i)) nxt &= ~(1 << i - 1), nxt &= ~(1 << i + 1);
            else nxt ^= (1 << i - 1), nxt ^= (1 << i + 1);
            if (dis[u] + 1 < dis[nxt]) dis[nxt] = dis[u] + 1, q[++ t] = nxt, pre[nxt][0] = u, pre[nxt][1] = i + 1;
        }
    }
    print(mx, ' ', dis[T], '\n');
    Print(T), print('\n');
}
inline bool check()
{
    for (rint i = 1; i <= n; ++ i)
        if (s[i] ^ 49) return false;
    return true;
}
int ans[13000005], tot;
signed main()
{
    freopen("shi.in", "r", stdin);
    freopen("shi.out", "w", stdout);
    for (read(T); T --;)
    {
        read(s + 1), n = strlen(s + 1);
        if (check()) print(n, ' ', 0, '\n', '\n');
        else if (n <= 5) bfs();
        else
        {
            tot = 0;
            for (rint i = 1; i < n - 1; ++ i)
                if (s[i] ^ 48) ans[++ tot] = i + 1, s[i] = '0', s[i + 2] = 49 ^ (s[i + 2] ^ 48 || s[i + 1] ^ 48);
            if (s[n] == '0' && s[n - 1] == '1') ans[++ tot] = n - 2, ans[++ tot] = n - 1, ans[++ tot] = n - 2, ans[++ tot] = n - 1;
            else if (s[n] == '1' && s[n - 1] == '0') ans[++ tot] = n - 2, ans[++ tot] = n - 1, ans[++ tot] = n - 2;
            else if (s[n] == '1' && s[n - 1] == '1') ans[++ tot] = n - 1, ans[++ tot] = n - 2, ans[++ tot] = n - 1, ans[++ tot] = n - 2, ans[++ tot] = n - 1;
            for (rint i = 1; i < n - 4; ++ i) ans[++ tot] = i + 1, ans[++ tot] = i + 3, ans[++ tot] = i + 2, ans[++ tot] = i + 3, ans[++ tot] = i + 2;
            ans[++ tot] = n - 3, ans[++ tot] = n - 1, ans[++ tot] = n - 2;
            print(n - 1, ' ', tot, '\n');
            for (rint i = 1; i <= tot; ++ i) print(ans[i], ' ');
            print('\n');
        }
    }
    return flush(), 0;
}