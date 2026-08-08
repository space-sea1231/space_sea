#include <bits/stdc++.h>
using namespace std;
#ifdef _WIN32
#define getchar() p1 == p2 && (p2 = (p1 = buf) + _fread_nolock(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
#else
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread_unlocked(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
#endif
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
#ifdef _WIN32
#define putchar(x) _putchar_nolock(x)
#else
#define putchar(x) putchar_unlocked(x)
#endif
template <class T>
void write(T x)
{
    static int stk[30];
    if (x < 0)
        putchar('-'), x = -x;
    int top = 0;
    do
    {
        stk[top++] = x % 10, x /= 10;
    } while (x);
    while (top)
        putchar(stk[--top] + '0');
}
template <class T>
void write(T x, char lastChar) { write(x), putchar(lastChar); }
template <typename T>
void chkmx(T &x, T y) { x = max(x, y); }
template <typename T>
void chkmn(T &x, T y) { x = min(x, y); }
int n, q;
char s[2'000'020];
int c[3][2'000'020];
int pre3[2'000'020];
int nxt3[2'000'020];
int pre[3][2'000'020];
int nxt[3][2'000'020];
inline bool ok(int a, int b, int c) { return a != b && a != c && b != c; }
void checkL(int l, int r, int &ansl, int &ansr)
{
    if (l > r)
        return;
    if (r - l + 1 <= ansr - ansl + 1)
        return;
    int cnt[3] = {c[0][r] - c[0][l - 1],
                  c[1][r] - c[1][l - 1],
                  c[2][r] - c[2][l - 1]};
    int tmp = 3;
    while (r >= l)
    {
        while (tmp > 0 && r >= l && !ok(cnt[0], cnt[1], cnt[2]))
        {
            tmp--;
            cnt[s[r] - 'A']--;
            r--;
            if (ok(cnt[0], cnt[1], cnt[2]))
                break;
            if (cnt[0] == cnt[1] && cnt[1] == cnt[2])
                break;
        }
        if (r < l)
            break;
        if (ok(cnt[0], cnt[1], cnt[2]))
            break;
        if (cnt[0] == cnt[1] && cnt[1] == cnt[2])
        {
            cnt[0] -= c[0][r] - c[0][pre3[r]];
            cnt[1] -= c[1][r] - c[1][pre3[r]];
            cnt[2] -= c[2][r] - c[2][pre3[r]];
            r = pre3[r];
            tmp = 3;
        }
        else
        {
            int sp = cnt[0] ^ cnt[1] ^ cnt[2];
            int sm = (cnt[0] + cnt[1] + cnt[2] - sp) >> 1;
            for (int i = 0; i < 3; i++)
            {
                if (cnt[i] != sp)
                    continue;
                int mxpos = 0;
                for (int j = 0; j < 3; j++)
                {
                    if (j == i)
                        continue;
                    chkmx(mxpos, pre[j][r]);
                }
                if (cnt[i] > sm)
                {
                    int gap = min(r - (mxpos + 1), cnt[i] - sm);
                    cnt[i] -= gap;
                    r -= gap;
                }
                else
                {
                    int gap = r - (mxpos + 1);
                    cnt[i] -= gap;
                    r -= gap;
                }
                break;
            }
            tmp = 3;
        }
    }
    if (r < l)
        return;
    if (r - l + 1 <= ansr - ansl + 1)
        return;
    ansl = l;
    ansr = r;
}
void checkR(int l, int r, int &ansl, int &ansr)
{
    if (l > r)
        return;
    if (r - l + 1 <= ansr - ansl + 1)
        return;
    int cnt[3] = {c[0][r] - c[0][l - 1],
                  c[1][r] - c[1][l - 1],
                  c[2][r] - c[2][l - 1]};
    int tmp = 3;
    while (l <= r)
    {
        while (tmp > 0 && l <= r && !ok(cnt[0], cnt[1], cnt[2]))
        {
            tmp--;
            cnt[s[l] - 'A']--;
            l++;
            if (ok(cnt[0], cnt[1], cnt[2]))
                break;
            if (cnt[0] == cnt[1] && cnt[1] == cnt[2])
                break;
        }
        if (l > r)
            break;
        if (ok(cnt[0], cnt[1], cnt[2]))
            break;
        if (cnt[0] == cnt[1] && cnt[1] == cnt[2])
        {
            cnt[0] -= c[0][nxt3[l] - 1] - c[0][l - 1];
            cnt[1] -= c[1][nxt3[l] - 1] - c[1][l - 1];
            cnt[2] -= c[2][nxt3[l] - 1] - c[2][l - 1];
            l = nxt3[l];
            tmp = 3;
        }
        else
        {
            int sp = cnt[0] ^ cnt[1] ^ cnt[2];
            int sm = (cnt[0] + cnt[1] + cnt[2] - sp) >> 1;
            for (int i = 0; i < 3; i++)
            {
                if (cnt[i] != sp)
                    continue;
                int mnpos = n + 1;
                for (int j = 0; j < 3; j++)
                {
                    if (j == i)
                        continue;
                    chkmn(mnpos, nxt[j][l]);
                }
                if (cnt[i] > sm)
                {
                    int gap = min((mnpos - 1) - l, cnt[i] - sm);
                    cnt[i] -= gap;
                    l += gap;
                }
                else
                {
                    int gap = (mnpos - 1) - l;
                    cnt[i] -= gap;
                    l += gap;
                }
                break;
            }
            tmp = 3;
        }
    }
    if (r < l)
        return;
    if (r - l + 1 <= ansr - ansl + 1)
        return;
    ansl = l;
    ansr = r;
}
int main()
{
    read(n);
    for (int i = 1; i <= n; i++)
    {
        while (s[i] != 'A' && s[i] != 'B' && s[i] != 'C')
            s[i] = getchar();
    }
    for (int j = 0; j < 3; j++)
    {
        for (int i = 1; i <= n; i++)
            c[j][i] = c[j][i - 1] + (s[i] == ('A' + j));
    }
    pre3[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i >= 3 && s[i] != s[i - 1] && s[i] != s[i - 2] && s[i - 1] != s[i - 2])
            pre3[i] = pre3[i - 3];
        else
            pre3[i] = i;
    }
    nxt3[n + 1] = n + 1;
    for (int i = n; i >= 1; i--)
    {
        if (i <= n - 2 && s[i] != s[i + 1] && s[i] != s[i + 2] && s[i + 1] != s[i + 2])
            nxt3[i] = nxt3[i + 3];
        else
            nxt3[i] = i;
    }
    for (int j = 0; j < 3; j++)
    {
        nxt[j][0] = 0;
        for (int i = 1; i <= n; i++)
            pre[j][i] = s[i] == 'A' + j ? i : pre[j][i - 1];
    }
    for (int j = 0; j < 3; j++)
    {
        nxt[j][n + 1] = n + 1;
        for (int i = n; i >= 1; i--)
            nxt[j][i] = s[i] == 'A' + j ? i : nxt[j][i + 1];
    }
    read(q);
    int last_ans = 0;
    while (q--)
    {
        int l, r;
        read(l, r);
        l = ((l ^ last_ans) + n - 1) % n + 1;
        r = ((r ^ last_ans) + n - 1) % n + 1;
        if (l > r)
            swap(l, r);
        int ansl = 0, ansr = 0;
        checkL(l, r, ansl, ansr);
        checkL(l + 1, r, ansl, ansr);
        checkL(l + 2, r, ansl, ansr);
        checkR(l, r, ansl, ansr);
        checkR(l, r - 1, ansl, ansr);
        checkR(l, r - 2, ansl, ansr);
        write(ansl, ' '), write(ansr, '\n');
        if (!ansl)
            last_ans = 0;
        else
            last_ans = ansr - ansl + 1;
    }
    return 0;
}
