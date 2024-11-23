#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n, m;
int head[N], nxt[N];
bool vis[N];
void add_1(int u, int v){
	nxt[head[v]]=u;
	head[u]=head[v];
	head[v]=u;
	nxt[u]=v;
}
void add_2(int u, int v){
	nxt[v]=nxt[u];
	head[nxt[u]]=v;
	head[v]=u;
	nxt[u]=v;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;
	nxt[0]=1;
	for (int i=2; i<=n; i++){
		int k, p;
		cin >> k >> p;
		if (p==0){
			add_1(i, k);
		}else{
			add_2(k, i);
		}
	}
	cin >> m;
	for (int i=1; i<=m; i++){
		int x;
		cin >> x;
		vis[x]=1;
	}
	for (int i=nxt[0]; ; i=nxt[i]){
		if (!vis[i]){
			printf("%d ", i);
		}
		if (!nxt[i]){
			break;
		}
	}

	return 0;
}