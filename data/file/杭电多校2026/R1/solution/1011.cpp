#include <bits/stdc++.h>
using namespace std;

struct DSU
{
    vector<int> p;
    DSU(int n) : p(n) { iota(p.begin(), p.end(), 0); }
    int find(int x)
    {
        while (p[x] != x)
            p[x] = p[p[x]], x = p[x];
        return x;
    }
    void join(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a != b)
            p[a] = b;
    }
};
int n, ecnt;
vector<int> eu, ev, val, cap, ins, vis;

bool augment()
{
    DSU dsu(n);
    for (int e = 0; e < ecnt; ++e)
        if (vis[e])
            dsu.join(eu[e], ev[e]);
    vector<int> fa(ecnt, -1), q(ecnt);
    int qh = 0, qt = 0;
    for (int e = 0; e < ecnt; ++e)
        if (!vis[e] && dsu.find(eu[e]) != dsu.find(ev[e]))
            fa[e] = -2, q[qt++] = e;
    int flg = -1;
    while (qh < qt && flg < 0)
    {
        int x = q[qh++];
        if (!vis[x])
        {
            int g = val[x];
            if (ins[g] < cap[g])
            {
                flg = x;
                break;
            }
            for (int y = 0; y < ecnt; ++y)
                if (vis[y] && val[y] == g && fa[y] == -1)
                    fa[y] = x, q[qt++] = y;
        }
        else
        {
            DSU without(n);
            for (int e = 0; e < ecnt; ++e)
                if (vis[e] && e != x)
                    without.join(eu[e], ev[e]);
            for (int y = 0; y < ecnt; ++y)
                if (!vis[y] && fa[y] == -1 && without.find(eu[y]) != without.find(ev[y]))
                    fa[y] = x, q[qt++] = y;
        }
    }
    if (flg < 0)
        return false;
    for (int x = flg; x != -2; x = fa[x])
    {
        if (vis[x])
            vis[x] = 0, --ins[val[x]];
        else
            vis[x] = 1, ++ins[val[x]];
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        int m, k;
        cin >> n >> m >> k;
        cap.resize(m);
        for (int &x : cap)
            cin >> x;
        ecnt = m * k;
        eu.resize(ecnt);
        ev.resize(ecnt);
        val.resize(ecnt);
        for (int graph = 0; graph < k; ++graph)
            for (int j = 0; j < m; ++j)
            {
                int id = graph * m + j;
                cin >> eu[id] >> ev[id];
                --eu[id];
                --ev[id];
                val[id] = j;
            }
        vis.assign(ecnt, 0);
        ins.assign(m, 0);
        int ans = 0;
        while (augment())
            ++ans;
        cout << ans << "\n";
    }
    return 0;
}
