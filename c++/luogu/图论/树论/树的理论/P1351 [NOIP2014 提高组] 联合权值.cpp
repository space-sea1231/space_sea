#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const int Mod=10007;
int head[N], to[N<<1], nxt[N<<1];
int w[N];
int n, cnt, ans, maxn;
void add(int u, int v){
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;
	for (int i=1; i<n; i++){
		int u, v;
		cin >> u >> v;
		add(u, v);
		add(v, u);
	}
	for (int i=1; i<=n; i++){
		cin >> w[i];
	}
	for (int i=1; i<=n; i++){
		int maxn_1=0, maxn_2=0;
		int x=0, y=0;
		for (int j=head[i]; j; j=nxt[j]){
			int v=to[j];
			if (w[v]>maxn_1){
				maxn_2=maxn_1;
				maxn_1=w[v];
			}else if (w[v]>maxn_2){
				maxn_2=w[v];
			}
			x=(x+w[v])%Mod;
			y=(y+w[v]*w[v])%Mod;
		}
		x=x*x%Mod;
		ans=(ans+x+Mod-y)%Mod;
		maxn=max(maxn, maxn_1*maxn_2);
	}
	printf("%d %d", maxn, ans);

	return 0;
}