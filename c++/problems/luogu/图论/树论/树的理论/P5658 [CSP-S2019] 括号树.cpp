#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int head[N], to[N], nxt[N], fa[N], s[N], sum[N], lst[N];
int n, cnt, top;
char c[N];
void add(int u, int v)
{
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
void dfs(int u)
{
	int tmp=0, v;
	if (c[u]==')')
	{
		if (top)
		{
			tmp=s[top--];
			lst[u]=lst[fa[tmp]]+1;
		}
	}
	else if (c[u]=='(') s[++top]=u;
	sum[u]=sum[fa[u]]+lst[u];
	for (int i=head[u]; i; i=nxt[i])
		v=to[i], dfs(v);

	if (tmp) s[++top]=tmp;
	else if (top) top--;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	int u;
	for (int i=1; i<=n; i++)
	{
		cin >> c[i];
	}
	for (int i=2; i<=n; i++)
	{
		cin >> u;
		add(u, i), fa[i]=u;
	}
	dfs(1);
	int ans=0;
	for (int i=1; i<=n; i++)
		ans^=sum[i]*i;
	printf("%lld", ans);

	return 0;
}