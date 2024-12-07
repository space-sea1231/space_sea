#include <bits/stdc++.h>
using namespace std;

const int maxn = 30;

int n, m;
vector<int> e[maxn];
int degree[maxn];
int a[maxn];
stack<int> s;
bool vis[maxn];
int mrk;

bool topo(int r)
{
    int sz = 0;
    bool finished = true;
    int t[maxn];
    for (int i = 0; i < n; i++)
    {
        t[i] = degree[i];
        if (!degree[i])
            s.push(i), vis[i] = true;
    }
    while (!s.empty())
    {
        if (s.size() > 1)
            finished = false;
        int k = s.top();
        a[sz++] = k;
        s.pop();
        for (int i = 0; i < e[k].size(); i++)
            t[e[k][i]]--;
        for (int i = 0; i < n; i++)
            if (!t[i] && !vis[i])
                s.push(i), vis[i] = true;
        ;
    }
    if (sz < n)
        return false;
    if (finished && !mrk)
        mrk = r;
    return true;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        char c[3];
        scanf("%s", c);
        int x = c[0] - 'A', y = c[2] - 'A';
        e[x].push_back(y);
        degree[y]++;
        if (!topo(i))
        {
            cout << "Inconsistency found after " << i << " relations.";
            return 0;
        }
        memset(vis, false, sizeof(vis));
    }
    if (mrk)
    {
        cout << "Sorted sequence determined after " << mrk << " relations: ";
        for (int i = 0; i < n; i++)
            cout << char(a[i] + 'A');
        cout << ".";
    }
    else
        cout << "Sorted sequence cannot be determined.";
    return 0;
}