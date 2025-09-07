#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5, mod = 998244353;
int t, n, a[N << 1], ans;
int quick_pow (int a, int b)
{
	if (b == 0)return 1;
	if (b == 1)return a;
	int ans = 1;
	if (b & 1)ans = a;
	int p = quick_pow (a, b >> 1);
	ans = ans * p * p; 
	return ans;
}
void solve ()
{
	cin >> n;
	ans = 0;
	for (int i = 1; i <= 2 * n; ++ i)
	{
		cin >> a[i];
		if (a[i] == 0)++ ans;
	}
	cout << quick_pow (2, ans - 1) << '\n';
}
signed main ()
{
	ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
	freopen ("wo.in", "r", stdin);
	freopen ("wo.out", "w", stdout);
	cin >> t;
	while (t --)solve ();
	return 0;
}
