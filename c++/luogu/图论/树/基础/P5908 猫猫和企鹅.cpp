#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int head[N], to[N<<1], nxt[N<<1];
int n, m, cnt, tot;
void add(int u, int v){
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
void serch(int u, int fa, int dep){
	if (dep>m){
		return ;
	}
	tot++;
	for (int i=head[u]; i; i=nxt[i]){
		int v=to[i];
		if (v==fa){
			continue;
		}
		serch(v, u, dep+1);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n >> m;
	for (int i=1; i<n; i++){
		int u, v;
		cin >> u >> v;
		add(u, v);
		add(v, u);
	}
	serch(1, 0, 0);
	printf("%d", tot-1);

	return 0;
}