#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int head[N], to[N<<1], nxt[N<<1], edge[N<<1];
int sum[N];
int n, cnt, ans;
void add(int u, int v, int w){
	to[++cnt]=v;
	edge[cnt]=w;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
void serch(int u, int fa){
	sum[u]=1;
	for (int i=head[u]; i; i=nxt[i]){
		int v=to[i], w=edge[i];
		if (v==fa){
			continue;
		}
		serch(v, u);
		sum[u]+=sum[v];
		ans+=w*abs(n-2*sum[v]);
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;
	for (int i=1; i<n; i++){
		int u, v, w;
		cin >> u >> v >> w;
		add(u, v, w);
		add(v, u, w);
	}
	serch(1, 0);
	printf("%lld", ans);

	return 0;
}