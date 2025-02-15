#include <bits/stdc++.h>
using namespace std;
#define int long long
int T, n, cnt = 0;
string a;
vector<int> v[2];
signed main()
{
    freopen("shi.in", "r", stdin);
    freopen("shi.out", "w", stdout);
    ios ::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> T;
    while (T--)
    {
        cin >> a;
        n = a.size();
        a = " " + a;
        int cnt = 0;
        for (int i = 1; i <= n; i++)
        {
            if (a[i] == '1')
            {
                cnt++;
            }
        }
        if (cnt == n)cout << cnt << ' ';
        else if (n <= 3)
        {
            if (a[2] == '1')
            {
                if (cnt == 2)
                {
                    cout << 2 << ' ';
                }
                else
                {
                    cout << 1 << ' ';
                }
            }
            else
            {
                cout << cnt << ' ';
            }
        }
        else
        {
            cout << n - 1 << ' ';
        }
        cout << "0 \n";
        // for (int i = 1; i <= n; i++)
        // {

        // }
    }
    return 0;
}