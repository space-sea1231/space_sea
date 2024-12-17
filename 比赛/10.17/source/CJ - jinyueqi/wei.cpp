#include <bits/stdc++.h>
// #pragma optimize (3,"Ofast","inline")
#define max(x,y) (x<y?y:x)
#define min(x,y) (x>y?y:x)
using namespace std;
const int N = 4e5 + 5;
int n , t , a[N] ;
unsigned long long dp[N] , res ;
signed main ()
{
	freopen ("wei.in" , "r" , stdin);
	freopen ("wei.out" , "w" , stdout);
    ios::sync_with_stdio (0); cin.tie (0); cout.tie (0);
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        unsigned long long ans = 0 , dw = 0 ;
        for (int i = 1; i <= n; i++)
        {
            dp[i] = 1;
            if (a[i] > a[i - 1]) dp[i] += dp[i - 1];
            ans += dp[i];
        }
        res = max (res , ans);
        int B = (n >= 500 ? 80 : 300);
        for (int p1 = 1; p1 <= n; p1++)
        {
            int l = max (p1 + 1 , a[p1] - B) , r = min (n , a[p1] + B);
            for (int p2 = l; p2 <= r; p2++)
            {
                a[p1] ^= a[p2] ^= a[p1] ^= a[p2];
                ans = dw;
                for (int i = p1; i <= n; i++)
                {
                    ans += (a[i] > a[i - 1] ? dp[i] = dp[i - 1] + 1 : dp[i] = 1);
                    if (ans + (n - i) * n <= res) break;
                }
                res = max (res , ans);
                a[p1] ^= a[p2] ^= a[p1] ^= a[p2];
            }
            dp[p1] = 1;
            if (a[p1] > a[p1 - 1]) dp[p1] += dp[p1 - 1];
            dw += dp[p1];
        }
        cout << res << "\n"; res = 0;
    }
	return 0;
}


