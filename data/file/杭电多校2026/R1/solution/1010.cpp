#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        vector<ll> pre(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            ll x;
            cin >> x;
            pre[i] = pre[i - 1] + x;
        }
        bool win;
        if (n == 1)
            win = 0;
        else if ((n & 1) == 0)
        {
            int k = n / 2;
            win = 1;
            for (int i = k; i >= 2; --i)
            {
                ll l = pre[i], r = pre[n] - pre[n - (i - 1)];
                if (l != r)
                {
                    win = l > r;
                    break;
                }
            }
        }
        else
        {
            int k = n / 2;
            win = 0;
            for (int i = k; i >= 1; --i)
            {
                ll l = pre[i], r = pre[n] - pre[n - i];
                if (l != r)
                {
                    win = l > r;
                    break;
                }
            }
        }
        cout << (win ? "YES\n" : "NO\n");
    }
    return 0;
}
