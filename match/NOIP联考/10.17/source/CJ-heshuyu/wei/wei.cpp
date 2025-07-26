#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 4e5 + 5;
int n, a[N], rmq[N][20], lg[N], diff[N], L[N], R[N], sum[N];
void RMQ()
{
    for(int i = 2; i <= n; i++)
        lg[i] = lg[i >> 1] + 1;
    memset(rmq, 0x3f, sizeof(rmq));
    for(int i = 1; i <= n; i++)
        rmq[i][0] = diff[i];
    for(int j = 1; (1 << j) <= n; j++)
        for(int i = 1; i + (1 << j) - 1 <= n; i++)
            rmq[i][j] = min(rmq[i][j - 1], rmq[i + (1 << j - 1)][j - 1]);
    return;
}
int query(int l, int r)
{
    int k = lg[r - l + 1];
    return min(rmq[l][k], rmq[r - (1 << k) + 1][k]);
}
int getL(int x)
{
    int lt = 0, rt = x;
    // cerr << x << endl;
    while(lt + 1 < rt)
    {
        int mid = lt + rt >> 1;
        // cerr << "x " << mid << endl;
        if(query(mid + 1, x) < 0)
            lt = mid;
        else
            rt = mid;
    }
    return x - rt + 1;
}
int getR(int x)
{
    int lt = x, rt = n + 1;
    while(lt + 1 < rt)
    {
        int mid = lt + rt >> 1;
        if(query(x + 1, mid) < 0)
            rt = mid;
        else
            lt = mid;
    }
    return lt - x + 1;
}
// int calc(int x, int y)
// {
//     int len = L[x] + R[x] - 1, len1 = len;
//     int l = L[x], r = R[x];
//     cerr << x << ' ' << y << endl;
//     if(a[y] < a[x + 1])
//     if(a[x] < a[y - 1])
//         r = min(r, y - x);
//     else
//     {
//         if(a[x] > a[y + 1])
//             r = min(r, y - x + 1);
//         else
//             r = max()
//     }
//     if(x + R[x] - 1 >= y)
//     {
//         if(x + R[x] - 1 == y && a[x] < a[y - 1])
//             len1 = L[x] + y - x - 1;
//         else if(x + R[x] - 1 > y && (a[x] < a[y - 1] || a[x] > a[y + 1]))
//             len1 = L[x] + y - x - 1;
//     }
//     int Len = L[y] + R[y] - 1, Len1 = Len;
//     if(y - L[y] + 1 <= x)
//     {
//         if(y - L[y] + 1 == x && a[y] > a[x + 1])
//             Len1 = R[y] + x - y - 1;
//         else if(y - L[y] + 1 < x && (a[y] > a[x + 1] || a[y] < a[x - 1]))
//             Len1 = R[y] + x - y - 1;
//     }
//     return ((len1 * (len1 + 1)) + (Len1 * (Len1 + 1)) - (len * (len + 1)) - (Len * (Len + 1))) / 2;
// }
signed main()
{
    freopen("wei.in", "r", stdin);
    freopen("wei.out", "w", stdout);
    cin.tie(0) -> sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i], diff[i] = a[i] - a[i - 1];
        int maxi = 0;
        for(int i = 1; i <= n; i++)
            for(int j = i + 1; j <= n; j++)
            {
                // if((a[j] < a[i - 1] && a[j] > a[i + 1]) || (a[i] < a[j - 1] && a))
                swap(a[i], a[j]);
                int len = 0;
                for(int k = 1; k <= n; k++)
                {
                    if(a[k] > a[k - 1])
                        len++;
                    else
                        len = 1;
                    // cerr << len << ' ' << k << endl;
                    sum[k] = sum[k - len] + len * (len + 1) / 2;
                }
                swap(a[i], a[j]);
                maxi = max(maxi, sum[n]);
            }
        cout << maxi << "\n";
    }
    return 0;
}