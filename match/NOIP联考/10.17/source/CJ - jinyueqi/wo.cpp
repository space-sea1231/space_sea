#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 6 , Mod = 998244353;
int t , n , p[N] , cnt[2];
bool vis[N];
vector <int> v;
inline long long calc (int x , bool de)
{
    long long ans = 1 , res = 0; cnt[0] = cnt[1] = 0;
    for (int i = 1; i <= n * 2; i++) if (!vis[i]) cnt[de ? i <= x : i < x]++;
    for (int i = 1; i <= n * 2; i += 2)
    {
        if (!p[i] && !p[i + 1]) 
        {
            ans = ans * cnt[0] % Mod * cnt[1] % Mod * 2 % Mod , cnt[0]-- , cnt[1]--;
            if (cnt[0] < 0 || cnt[1] < 0) return -1;
        }
        else if (!p[i] && p[i + 1]) ans = ans * cnt[p[i + 1] > x] % Mod , cnt[p[i + 1] > x]--;
        else if (p[i] && !p[i + 1]) ans = ans * cnt[p[i] > x] % Mod , cnt[p[i] > x]--;
    }
    return ans;
}
inline long long doit (int x)
{
    return max (calc (x , 0) , calc (x , 1));
}
signed main ()
{
	freopen ("wo.in" , "r" , stdin);
	freopen ("wo.out" , "w" , stdout);
	ios::sync_with_stdio (0); cin.tie (0); cout.tie (0);
	cin >> t ;
	while (t--)
	{
		cin >> n; v.clear ();
		for (int i = 1; i <= n * 2; i++) vis[i] = 0; cnt[0] = cnt[1] = 0;
		for (int i = 1; i <= n * 2; i++) cin >> p[i] , vis[p[i]] = 1;
		for (int i = 1; i <= n * 2; i++) if (!vis[i]) v.push_back (i);
        // cerr << "Now: \n";
        // for (auto i : v) cerr << i << " " ; cerr << "\n\n";
        int l = 1 , r = n * 2; long long ans = 1;
        // for (int i = 1; i <= r; i++)
        // {
        //     if (doit (i) >= ans)
        //         ans = doit (i) , cerr << i << "\n";
        // }
        // cerr << "\n\n";
        while (l <= r)
        {
            int mid = l + r >> 1;
            ans = max (ans , doit (mid));
            // cerr << mid << "\n";
            if (cnt[0] < cnt[1]) r = mid - 1;
            else l = mid + 1;
        }
		cout << ans << "\n"; ans = 1;
	}
	return 0;
}
