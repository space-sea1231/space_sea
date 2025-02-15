#include <bits/stdc++.h>
using namespace std;
void file(string x)
{
    freopen((x + ".in").c_str(), "r", stdin);
    freopen((x + ".out").c_str(), "w", stdout);
}
const int maxn = 1e6 + 5;
char mp[maxn];
int val[maxn], tval[maxn], n;
int d(int x, int y)
{
    return !(x | y);
}
void cz(int x)
{
    val[x - 1] = d(val[x - 1], val[x]);
    val[x + 1] = d(val[x + 1], val[x]);
}
int maxx;
vector<int> vec, vans;
void solve1()
{
    vec.clear();
    for (int i = 1; i <= n; i++) val[i] = tval[i];
    for (int i = 1; i < n - 1; i++)
    {
        if (!val[i])
        {
            if (!val[i + 1])
                vec.emplace_back(i + 1), cz(i + 1);
            else
            {
                if (i + 2 < n)
                {
                    vec.emplace_back(i + 2), cz(i + 2);
                    assert(!val[i + 1]);
                    vec.emplace_back(i + 1), cz(i + 1);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans += val[i], val[i] = tval[i];
    if (ans > maxx) maxx = ans, vans = vec;
}
void solve2()
{
    vec.clear();
    for (int i = 1; i <= n; i++) val[i] = tval[i];
    for (int i = 1; i < n - 2; i++)
    {
        if (!val[i])
        {
            if (!val[i + 1])
                vec.emplace_back(i + 1), cz(i + 1);
            else
            {
                if (i + 2 < n)
                {
                    vec.emplace_back(i + 2), cz(i + 2);
                    assert(!val[i + 1]);
                    vec.emplace_back(i + 1), cz(i + 1);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans += val[i], val[i] = tval[i];
    if (ans > maxx) maxx = ans, vans = vec;
}
void solve3()
{
    for (int i = 1; i <= n; i++) val[i] = tval[i];
    vec.clear();
    if (val[n] != 1 && n >= 3)
    {
        if (!val[n - 1]) vec.emplace_back(n - 1), cz(n - 1);
        else if (n >= 4) vec.emplace_back(n - 2), cz(n - 2), vec.emplace_back(n - 1), cz(n - 1);
    }
    for (int i = 1; i < n - 2; i++)
    {
        if (!val[i])
        {
            if (!val[i + 1])
                vec.emplace_back(i + 1), cz(i + 1);
            else
            {
                if (i + 2 < n)
                {
                    vec.emplace_back(i + 2), cz(i + 2);
                    assert(!val[i + 1]);
                    vec.emplace_back(i + 1), cz(i + 1);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans += val[i], val[i] = tval[i];
    if (ans > maxx) maxx = ans, vans = vec;
}
void solve4()
{
    for (int i = 1; i <= n; i++) val[i] = tval[i];
    vec.clear();
    if (val[n] != 1 && n >= 3)
    {
        if (!val[n - 1]) vec.emplace_back(n - 1), cz(n - 1);
        else if (n >= 4) vec.emplace_back(n - 2), cz(n - 2), vec.emplace_back(n - 1), cz(n - 1);
    }
    for (int i = 1; i < n - 1; i++)
    {
        if (!val[i])
        {
            if (!val[i + 1])
                vec.emplace_back(i + 1), cz(i + 1);
            else
            {
                if (i + 2 < n)
                {
                    vec.emplace_back(i + 2), cz(i + 2);
                    assert(!val[i + 1]);
                    vec.emplace_back(i + 1), cz(i + 1);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans += val[i], val[i] = tval[i];
    if (ans > maxx) maxx = ans, vans = vec;
}
void solve()
{
    cin >> (mp + 1);
    n = strlen(mp + 1);
    maxx = 0;
    vans.clear();
    for (int i = 1; i <= n; i++) val[i] = mp[i] - '0';
    for (int i = 1; i <= n; i++) tval[i] = val[i];
    solve1();
    solve2();
    solve3();
    solve4();
    cout << maxx << ' ' << vans.size() << '\n';
    for (int i : vans) cout << i << ' ';
    cout << '\n';
}
int main()
{
    file("shi");
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}