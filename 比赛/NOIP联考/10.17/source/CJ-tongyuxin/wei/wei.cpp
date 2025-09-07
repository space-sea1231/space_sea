#include <bits/stdc++.h>
#define N 400005
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
int T, n, a[N]; ll ans;
inline ll calc()
{
    rll res = 0;
    for (rint i = 1; i <= n; ++ i)
    {
        ++ res;
        rint j = i + 1;
        while (j <= n && a[j] > a[j - 1]) ++ res, ++ j;
    }
    return res;
}
signed main()
{
    freopen("wei.in", "r", stdin);
    freopen("wei.out", "w", stdout);
    for (read(T); T --;)
    {
        read(n);
        for (rint i = 1; i <= n; ++ i) read(a[i]);
        ans = calc();
        for (rint i = 1; i <= n; ++ i)
            for (rint j = i + 1; j <= n; ++ j)
                if (a[i] > a[j]) swap(a[i], a[j]), ans = max(ans, calc()), swap(a[i], a[j]);
        print(ans % 4294967296, '\n');
    }
    return flush(), 0;
}