#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 998442353;
struct node 
{
	int p[17] ;
} a[25];
int t , n , m , s[111] , mini , ans;
map < node , int > cnt , vis , dis , in;
inline void bfs (int id)
{
//	queue <node> q;
//	q.push (a[id]); vis[a[id]] = 1; in[a[id]] = 1;
//	cnt[a[id]] = 1;
//	while (q.size ())
//	{
//		node u = q.front (); q.pop ();
//		for (int i = 1; i <= n; i++)
//		{
//			node x = u; x.p[i]++;
//			if (!vis[a[id]])
//			{
//				dis[x] = dis[u] + 1; cnt[x] = cnt[u];
//				q.push (x); vis[a[id]] = 1;
//			}
////			else if (dis[x] == dis[u] + 1) cnt[]
//		}
//		for (int i = 1; i <= n; i++)
//		{
//			node x = u; x.p[i]--;
//			if (!vis[a[id]])
//			{
//				dis[x] = dis[u] + 1;
//				q.push (x); vis[a[id]] = 1;
//			}
//		}
//	}
}
signed main ()
{
	freopen ("ge.in" , "r" , stdin);
	freopen ("ge.out" , "w" , stdout);
	cin >> t;
	while (t--)
	{
		cin >> n >> m; ans = 0 , mini = 1e18;
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++)
				cin >> a[i].p[j];
		for (int i = 1; i <= m; i++) cin >> s[i];
//		for (int i = 1; i <= m; i++)
//			if (s[i] == 1) bfs (i);
//		if (mini >= 1e16) 
			cout << "NIE\n";
//		else cout << mini << " " << ans << "\n";
	}
	return 0;
}


