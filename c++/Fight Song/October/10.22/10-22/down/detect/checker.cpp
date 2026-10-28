#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 7, M = 1e6 + 7;
const int Mod = 998244353;

int n, m, idx;
int h[N], e[M], ne[M], d[N], f[N];

bool check(InStream &in, int &res) {
    idx = 0;
    fill(h, h + n + 1, -1);
    fill(d, d + n + 1, 0);
    fill(f, f + n + 1, 0);

    bool flag = true;
    for (int i = 1; i <= m; i ++) {
        int u = in.readInt(1, n, "u");
        int v = in.readInt(1, n, "v");

        if (u == v) flag = false;

        e[++ idx] = v;
        ne[idx] = h[u];
        h[u] = idx;
        d[v] ++;
    }

    if (!flag) return false;

    queue<int> q;
    for (int i = 1; i <= n; i ++)
        if (!d[i]) q.push(i);

    f[1] = 1;
    int cnt = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cnt ++;

        for (int i = h[u]; i != -1; i = ne[i]) {
            int v = e[i];
            f[v] = (f[v] + (long long)f[u]) % Mod;
            if (!-- d[v]) q.push(v);
        }
    }

    if (cnt < n) return false;

    res = f[n];
    return true;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 100000, "n");
    m = inf.readInt(1, 1000000, "m");

    int ja = ans.readInt(0, Mod - 1, "ans");
    if (!ans.seekEof())
        quitf(_fail, "extra jury output");

    int pa = ouf.readInt(0, Mod - 1, "ans");
    int pr;

    if (!check(ouf, pr))
        quitf(_wa, "the graph is illegal");

    if (!ouf.seekEof())
        quitf(_wa, "extra output");

    if (pa != ja)
        quitf(_wa, "expected %d, found %d", ja, pa);

    if (pr != ja)
        quitp(0.4, "right answer but wrong graph");

    quitf(_ok, "correct");
}