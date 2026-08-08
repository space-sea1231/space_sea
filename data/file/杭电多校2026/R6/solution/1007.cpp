#include <bits/stdc++.h>
using namespace std;

namespace IO
{
    constexpr int S = 1 << 20;
    char b1[S], *p1, *p2;
    char b2[S], *p3 = b2;
    #define G (p1 == p2 && (p2 = (p1 = b1) + fread(b1, 1, S, stdin)), *p1 ++)
    #define P (p3 == b2 + S && (fwrite(b2, S, 1, stdout), p3 = b2), *p3 ++)

    int R()
    {
        int x = 0, c = G;
        while (!isdigit(c)) c = G;
        while (isdigit(c)) x = x * 10 + (c & 15), c = G;
        return x;
    }

    void W(int x, char c)
    {
        static char stk[10]; int top = 0;
        do stk[top ++] = x % 10 | '0', x /= 10; while (x);
        while (top --) P = stk[top];
        P = c;
    }

    void flush()
    {
        fwrite(b2, p3 - b2, 1, stdout);
    }
}
using IO::R;
using IO::W;

constexpr int N = 1679616, B = 6;
constexpr int MOD = 100000007, INV2 = (MOD + 1) / 2;

int n, m;
int pwB[9], tmp[B], tmq[B];
int arr[N], brr[N], crr[N];

void FWT(int val[])
{
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < m; j += pwB[i + 1])
            for (int k = j; k < j + pwB[i]; k ++)
            {
                for (int u = 0; u < B; u ++) tmp[u] = val[k + u * pwB[i]];
                tmq[0] = tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + tmp[5];
                tmq[1] = tmp[1] + tmp[5];
                tmq[2] = tmp[1] - tmp[2] + tmp[4] - tmp[5];
                tmq[3] = tmp[1] + tmp[3] + tmp[5];
                tmq[4] = tmp[1] + tmp[2] + tmp[4] + tmp[5];
                tmq[5] = tmp[1] - tmp[5];
                for (int u = 0; u < B; u ++) val[k + u * pwB[i]] = (tmq[u] % MOD + MOD) % MOD;
            }
}

void IFWT(int val[])
{
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < m; j += pwB[i + 1])
            for (int k = j; k < j + pwB[i]; k ++)
            {
                for (int u = 0; u < B; u ++) tmp[u] = val[k + u * pwB[i]];
                tmq[0] = (tmp[0] + tmp[1] - tmp[3] - tmp[4]) * 2;
                tmq[1] = tmp[1] + tmp[5];
                tmq[2] = -tmp[1] - tmp[2] + tmp[4] + tmp[5];
                tmq[3] = (-tmp[1] + tmp[3]) * 2;
                tmq[4] = -tmp[1] + tmp[2] + tmp[4] - tmp[5];
                tmq[5] = tmp[1] - tmp[5];
                for (int u = 0; u < B; u ++) val[k + u * pwB[i]] = (1ll * tmq[u] * INV2 % MOD + MOD) % MOD;
            }
}

void solve()
{
    n = R();

    pwB[0] = 1;
    for (int i = 1; i <= n; i ++) pwB[i] = pwB[i - 1] * B;
    m = pwB[n];

    for (int i = 0; i < m; i ++) arr[i] = R();
    for (int i = 0; i < m; i ++) brr[i] = R();
    
    FWT(arr), FWT(brr);
    for (int i = 0; i < m; i ++) crr[i] = 1ll * arr[i] * brr[i] % MOD;
    IFWT(crr);

    for (int i = 0; i < m; i ++) W(crr[i], " \n"[i + 1 == m]);
}

int main()
{
    int T = R();
    while (T --> 0) solve();

    IO::flush();
    return 0;
}
