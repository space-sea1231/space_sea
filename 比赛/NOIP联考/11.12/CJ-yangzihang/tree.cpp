#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int n, cnt, start_1, start_2;
int dep_1[N], dep_2[N];
int head[N], to[N*2], nxt[N*2];
void add(int u, int v){
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
void init(){
	for (int i=1; i<N; i++){
		dep_1[i]=0;
	}
	dep_1[0]=-1;
}
void serch(int u, int fa){
	dep_1[u]=dep_1[fa]+1;
	for (int i=head[u]; i; i=nxt[i]){
		int v=to[i];
		if (v==fa){
			continue;
		}
		serch(v, u);
	}
}
int main(){
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;
	for (int i=1; i<n; i++){
		int u, v;
		cin >> u >> v;
		add(u, v);
		add(v, u);
	}
	init();
	serch(1, 0);
	for (int i=1; i<=n; i++){
		if (dep_1[i]>dep_1[start_1]){
			start_1=i;
		}
	}
	init();
	serch(start_1, 0);
	for (int i=1; i<=n; i++){
		if (dep_1[i]>dep_1[start_2]){
			start_2=i;
		}
		dep_2[i]=dep_1[i];
	}
	init();
	serch(start_2, 0);
	for (int i=1; i<=n; i++){
		dep_1[i]=max(dep_1[i], dep_2[i]);
	}
	sort(dep_1+1, dep_1+n+1);
	int top=1;
	for (int i=1; i<=n; i++){
		while (top<=n&&dep_1[top]<i){
			top++;
		}
		top=min(n, top);
		printf("%d ", top);
	}
	
	return 0;
}