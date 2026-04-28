#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, m;
double a[N];

namespace SegmentTree
{
    struct Node
    {
        double maxn;
        int sum;
    };

    Node node[N << 2];

    void Up(int x)
    {
        node[x].maxn = max(node[x << 1].maxn, node[x << 1 | 1].maxn);
    }

    int Down(int x, int l, int r, double val)
    {
        if (l == r)
            return a[l] > val;
        if (node[x].maxn <= val)
            return 0;
        if (a[l] > val)
            return node[x].sum;
        int mid = l + r >> 1;
        if (node[x << 1].maxn <= val)
            return Down(x << 1 | 1, mid + 1, r, val);
        else
            return Down(x << 1, l, mid, val) + node[x].sum - node[x << 1].sum;
    }

    void Change(int x, int l, int r, int pos, int val)
    {
        if (l == r)
        {
            node[x].maxn = (double)val / pos;
            node[x].sum = 1;
            return;
        }
        int mid = l + r >> 1;
        if (pos <= mid)
            Change(x << 1, l, mid, pos, val);
        if (mid + 1 <= pos)
            Change(x << 1 | 1, mid + 1, r, pos, val);
        Up(x);
        node[x].sum = node[x << 1].sum + Down(x << 1 | 1, mid + 1, r, node[x << 1].maxn);
    }
}
using namespace SegmentTree;

signed main()
{
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        cin >> x >> y;
        a[x] = (double)y / x;
        Change(1, 1, n, x, y);
        printf("%d\n", node[1].sum);
    }
    return 0;
}